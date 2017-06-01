#include <ape/graphics/batch_renderer.h>
#include <ape/core/transform.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ape {

    BatchRenderer::BatchRenderer(GLuint textureId) : textureId(textureId) { }

    GLuint BatchRenderer::getTextureId() {
        return textureId;
    }

    void BatchRenderer::addMesh(Mesh mesh) {
        meshDrawList.push_back(mesh);
    }

    void BatchRenderer::drawAll(World& world, Buffer<GLfloat>& attributeVBO, Buffer<GLfloat>& matrixVBO) {
        attributeVBO.bind();

        int listSize = meshDrawList.size();

        GLfloat *attributePointer = (GLfloat*)glMapBufferRange(GL_ARRAY_BUFFER, 0,
            listSize * 4 * (VertexAttributeInfo::ColorSize + VertexAttributeInfo::TextureSize),
            GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

        assert(attributePointer != NULL);

        std::vector<glm::mat4> transformations;

        int dataOffset = 0;

        for(auto& mesh : meshDrawList) {
            if(world.entityHasComponent<Transform>(mesh.entity)) {
                auto& transform = world.getComponent<Transform>(mesh.entity);
                auto& vertices = mesh.getVertices();

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

                // TODO: test this
                spriteTransform = glm::translate(spriteTransform, glm::vec3(
                    -mesh.getOrigin().x, -mesh.getOrigin().x, 0.f
                ));

                transformations.push_back(spriteTransform);
            }
        }

        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        matrixVBO.bind();

        GLfloat *matrixPointer = (GLfloat*)glMapBufferRange(GL_ARRAY_BUFFER, 0,
            listSize * 4 * 3, GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
        assert(matrixPointer != NULL);

        int count = 0;
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
    }

    int BatchRenderer::getMeshListSize() {
        return meshDrawList.size();
    }
}
