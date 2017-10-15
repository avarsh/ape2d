#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <vector>
#include <ape/core/world.h>
#include <ape/graphics/sprite.h>
#include <ape/graphics/shader.h>

namespace ape {

    class Renderer {
    public:
        Renderer();
        ~Renderer();

        void begin();
        void draw(Sprite* sprite);
        void end(Shader& shader, Texture& texture);
    private:
        std::vector<Sprite*> spriteList;

        GLfloat quadVertices[8] = {
            // Position // Texture - TEMPORARY
            0.f, 0.f,
            0.f, 1.f,
            1.f, 1.f,
            1.f, 0.f
        };

        GLushort indices[6] = {
            0, 1, 2,
            0, 2, 3
        };

        std::vector<float> transforms;
        std::vector<GLfloat> uv;

        GLuint vertexArray, quadVBO, quadEBO, instVBO, vertTBO, vertTexture;

        int toRender {0};
        int rendered {0};

        int instanceDataSize {4};
    };
}

#endif // RENDERER_H
