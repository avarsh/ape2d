#ifndef SPRITE_BATCHER_H
#define SPRITE_BATCHER_H

#include <vector>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ape/ecs/world.h>
#include <ape/graphics/vertex_attributes.h>
#include <ape/graphics/buffer.h>

namespace ape {

    class SpriteBatcher {
    public:
        void generateBuffers(int ID);

        void draw(World& world);

        void deleteBuffers();
    private:
        GLfloat square[8] = {
            0.f, 0.f,
            0.f, 1.f,
            1.f, 1.f,
            1.f, 0.0f
        };

        GLushort indices[6] = {
            0, 1, 2,
            0, 2, 3
        };

        GLuint vertexArray;

        Buffer<GLfloat> vertexBuffer, attributeBuffer, transformationBuffer;
        Buffer<GLushort> indexBuffer;

        int maxSize {65536};

        int ID;
    };
}

#endif
