#include <ape/graphics/sprite_batcher.h>
#include <ape/graphics/mesh.h>
#include <ape/graphics/sprite.h>
#include <ape/core/transform.h>

#include <cassert>

#define APE_PI 3.1415926535

namespace ape {

    void SpriteBatcher::generateBuffers(int ID) {

        this->ID = ID;

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

        vertexBuffer.init(GL_ARRAY_BUFFER, square, sizeof(square), false);
        indexBuffer.init(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices), false);

        vertexBuffer.bind();

        glVertexAttribPointer(LOCATION_POSITION, AttributeSizes::Position,
            GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(LOCATION_POSITION);

        // ==========================
        // The buffer for each vertex
        // ==========================

        attributeBuffer.init(GL_ARRAY_BUFFER, NULL, maxSize, true);

        int size = AttributeSizes::Color + AttributeSizes::Texture;

        glVertexAttribPointer(LOCATION_COLOR, AttributeSizes::Color,
            GL_FLOAT, GL_FALSE, size * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(LOCATION_COLOR);

        glVertexAttribPointer(LOCATION_TEXTURE, AttributeSizes::Texture,
            GL_FLOAT, GL_FALSE, size * sizeof(GLfloat), (GLvoid*)
            (AttributeSizes::Color * sizeof(GLfloat)));
        glEnableVertexAttribArray(LOCATION_TEXTURE);

        // ============================
        // The buffer for each instance
        // ============================

        transformationBuffer.init(GL_ARRAY_BUFFER, NULL, maxSize, true);

        for(int column = 0; column < 4; column++) {
            glVertexAttribPointer(3 + column, 3, GL_FLOAT, GL_FALSE,
                12 * sizeof(GLfloat), (GLvoid*)(column * 3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(3 + column);
            glVertexAttribDivisor(3 + column, 1);
        }

        // =========
        // Unbinding
        // =========

        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void SpriteBatcher::draw(World& world) {

        auto& spriteList = world.getComponentList<Sprite>();
        int listSize = spriteList.size();

        if(listSize > 0) {

            attributeBuffer.bind();

            GLfloat *attributePointer = (GLfloat*)glMapBufferRange(GL_ARRAY_BUFFER, 0,
                listSize * 4 * 5, GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

            assert(attributePointer != NULL);

            std::vector<glm::mat4> transformations;

            int dataOffset = 0;
            for(auto& sprite : spriteList) {

                if(sprite.batchID == this->ID) {

                    // TODO: check if sprite has these? Maybe throw an exception...
                    // Although this will call an assert if in debug mode
                    auto& mesh = world.getComponent<Mesh>(sprite.entity);
                    auto& transform = world.getComponent<Transform>(sprite.entity);

                    for(int index = 0; index < mesh.vertices.size(); index++) {
                        auto& vertex = mesh.vertices[index];

                        attributePointer[dataOffset]        = vertex.color.red;
                        attributePointer[dataOffset + 1]    = vertex.color.green;
                        attributePointer[dataOffset + 2]    = vertex.color.blue;
                        attributePointer[dataOffset + 3]    = vertex.texture.x;
                        attributePointer[dataOffset + 4]    = vertex.texture.y;

                        dataOffset += 5;
                    }

                    // Calculate transforms...
                    glm::mat4 spriteTransform;

                    spriteTransform = glm::translate(spriteTransform, glm::vec3(
                        transform.position.x, transform.position.y, 0.f
                    ));

                    spriteTransform = glm::scale(spriteTransform, glm::vec3(
                        sprite.dimensions.x, sprite.dimensions.y, 1.f
                    ));

                    spriteTransform = glm::rotate(spriteTransform, transform.rotation,
                        glm::vec3(0.0f, 0.0f, 1.f));

                    spriteTransform = glm::translate(spriteTransform, glm::vec3(
                        mesh.origin.x, mesh.origin.x, 0.f
                    ));

                    transformations.push_back(spriteTransform);
                }
            }

            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            transformationBuffer.bind();

            GLfloat *transformPointer = (GLfloat*)glMapBufferRange(GL_ARRAY_BUFFER, 0,
                listSize * 4 * 3, GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
            assert(transformPointer != NULL);

            int count = 0;
            for(auto& transform : transformations) {
                for(int column = 0; column < 4; column++) {
                    transformPointer[count]         = transform[column].x;
                    transformPointer[count + 1]     = transform[column].y;
                    transformPointer[count + 2]     = transform[column].z;

                    count += 3;
                }
            }

            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindVertexArray(vertexArray);
            glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0, listSize);
            glBindVertexArray(0);
        }
    }

    void SpriteBatcher::deleteBuffers() {
        glDeleteVertexArrays(1, &vertexArray);

        vertexBuffer.deleteBuffer();
        indexBuffer.deleteBuffer();
        attributeBuffer.deleteBuffer();
        transformationBuffer.deleteBuffer();
    }
}
