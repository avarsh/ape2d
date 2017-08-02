#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <vector>
#include <ape/core/world.h>
#include <ape/graphics/sprite.h>

namespace ape {

    class Renderer {
    public:
        Renderer();
        ~Renderer();

        void begin();
        void draw(Sprite* sprite);
        void end(World& world);
    private:
        std::vector<Sprite*> spriteList;

        GLfloat quadVertices[16] = {
            // Position // Texture - TEMPORARY
            0.f, 0.f,       0.0f, 1.0f,
            0.f, 1.f,       0.0f, 0.0f,
            1.f, 1.f,       1.0f, 0.0f,
            1.f, 0.f,       1.0f, 1.0f
        };

        GLushort indices[6] = {
            0, 1, 2,
            0, 2, 3
        };

        std::vector<float> transforms;

        GLuint vertexArray, quadVBO, quadEBO, instVBO;

        int toRender {0};
        int rendered {0};

        int instanceDataSize {4};
    };
}

#endif // RENDERER_H
