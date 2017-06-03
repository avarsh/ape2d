#include <ape/graphics/batch_renderer.h>
#include <ape/core/transform.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ape {

    BatchRenderer::BatchRenderer() {
        // ================
        // Generate buffers
        // ================

        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        // =====================
        // Initalise the buffers
        // =====================

        // ======================
        // Buffers for the square
        // ======================

        squareVBO.init(GL_ARRAY_BUFFER, square, sizeof(square), false);
        squareEBO.init(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices), false);

        squareVBO.bind();

        glVertexAttribPointer(VertexAttributeInfo::PositionLocation,
            VertexAttributeInfo::PositionSize, GL_FLOAT, GL_FALSE,
            VertexAttributeInfo::PositionSize * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(VertexAttributeInfo::PositionLocation);

        // ==========================
        // The buffer for each vertex
        // ==========================

        attributeVBO.init(GL_ARRAY_BUFFER, NULL, maxSize, true);
        attributeVBO.bind();

        int size = VertexAttributeInfo::ColorSize + VertexAttributeInfo::TextureSize;

        glVertexAttribPointer(VertexAttributeInfo::ColorLocation,
            VertexAttributeInfo::ColorSize, GL_FLOAT, GL_FALSE,
            size * sizeof(GLfloat), (GLvoid*)0);

        glEnableVertexAttribArray(VertexAttributeInfo::ColorLocation);

        glVertexAttribPointer(VertexAttributeInfo::TextureLocation,
            VertexAttributeInfo::TextureSize, GL_FLOAT, GL_FALSE,
            size * sizeof(GLfloat), (GLvoid*)(VertexAttributeInfo::ColorSize * sizeof(GLfloat)));

        glEnableVertexAttribArray(VertexAttributeInfo::TextureLocation);

        // ============================
        // The buffer for each instance
        // ============================

        matrixVBO.init(GL_ARRAY_BUFFER, NULL, maxSize, true);

        for(int column = 0; column < 4; column++) {
            glVertexAttribPointer(VertexAttributeInfo::TextureLocation + 1 + column, 3, GL_FLOAT, GL_FALSE,
                12 * sizeof(GLfloat), (GLvoid*)(column * 3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(VertexAttributeInfo::TextureLocation + 1 + column);
            glVertexAttribDivisor(VertexAttributeInfo::TextureLocation + 1 + column, 1);
        }

        // =========
        // Unbinding
        // =========

        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void BatchRenderer::setTextureId(GLuint textureId) {
        this->textureId = textureId;
    }

    GLuint BatchRenderer::getTextureId() {
        return textureId;
    }

    void BatchRenderer::addMesh(Mesh mesh) {
        meshDrawList.push_back(mesh);
    }

    void BatchRenderer::begin() {
        rendered = 0;
        //meshDrawList.clear();
    }

    void BatchRenderer::flush(World& world) {

        // Bind the per-vertex attribute buffer
        attributeVBO.bind();

        int listSize = meshDrawList.size();
        // We have color and texture attrbiutes, so each vertex receives
        // 3 + 2 = 5 values
        int attributeDataSize = VertexAttributeInfo::ColorSize + VertexAttributeInfo::TextureSize;

        // Rendered is how many instances we have rendered so far
        // There are 4 vertices for each instance
        int start = (rendered * 4 * attributeDataSize);
        int length = listSize * 4 * attributeDataSize;

        // Map the buffer
        GLfloat *attributePointer = (GLfloat*)glMapBufferRange(GL_ARRAY_BUFFER, 0,
            length + start,  GL_MAP_WRITE_BIT);

        assert(attributePointer != NULL);

        std::vector<glm::mat4> transformations;

        int dataOffset = start;
        int renderedThisFlush = 0;

        // Iterate over the meshes which the batcher has to draw
        for(auto& mesh : meshDrawList) {
            if(world.entityHasComponent<Transform>(mesh.entity)) {
                auto& transform = world.getComponent<Transform>(mesh.entity);
                auto& vertices = mesh.getVertices();

                // Send the corresponsing data for each vertex in the mesh
                for(int index = 0; index < vertices.size(); index++) {
                    auto& vertex = vertices[index];

                    attributePointer[dataOffset]        = vertex.color.red;
                    attributePointer[dataOffset + 1]    = vertex.color.green;
                    attributePointer[dataOffset + 2]    = vertex.color.blue;
                    attributePointer[dataOffset + 3]    = vertex.texture.x;
                    attributePointer[dataOffset + 4]    = vertex.texture.y;

                    dataOffset += 5;
                }

                // Calculate transformations
                glm::mat4 spriteTransform;

                spriteTransform = glm::translate(spriteTransform, glm::vec3(
                    transform.position.x, transform.position.y, 0.f
                ));

                spriteTransform = glm::scale(spriteTransform, glm::vec3(
                    mesh.getTextureRect().size.x, mesh.getTextureRect().size.y, 1.f
                ));

                spriteTransform = glm::rotate(spriteTransform, transform.rotation,
                    glm::vec3(0.0f, 0.0f, 1.f));

                spriteTransform = glm::translate(spriteTransform, glm::vec3(
                    -mesh.getOrigin().x, -mesh.getOrigin().x, 0.f
                ));

                transformations.push_back(spriteTransform);
                renderedThisFlush++;
            }
        }

        glUnmapBuffer(GL_ARRAY_BUFFER);

        // Write to the per-instance transformation VBO
        matrixVBO.bind();

        // There are 4 columns, each with 3 rows
        // (The last row is not included and is added in the shader)
        start =  rendered * 4 * 3;
        length = listSize * 4 * 3;

        GLfloat *matrixPointer = (GLfloat*)glMapBufferRange(GL_ARRAY_BUFFER, 0,
            length + start, GL_MAP_WRITE_BIT);

        assert(matrixPointer != NULL);

        // For each column in each transformation matrix, write the rows
        // to the buffer
        int count = start;
        for(auto& transform : transformations) {
            for(int column = 0; column < 4; column++) {
                matrixPointer[count]         = transform[column].x;
                matrixPointer[count + 1]     = transform[column].y;
                matrixPointer[count + 2]     = transform[column].z;

                count += 3;
            }
        }

        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Draw elements, using the number of instances we have
        // rendered so far as the base instance
        glBindVertexArray(vertexArray);
        glDrawElementsInstancedBaseInstance(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0, renderedThisFlush, rendered);
        glBindVertexArray(0);

        meshDrawList.clear();
        rendered += renderedThisFlush;
    }
}
