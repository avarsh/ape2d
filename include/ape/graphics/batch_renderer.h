#ifndef BATCH_RENDERER_H
#define BATCH_RENDERER_H

#include <vector>
#include <stack>
#include <ape/core/world.h>
#include <ape/graphics/mesh.h>
#include <ape/graphics/buffer.h>

namespace ape {
    class BatchRenderer {
    public:
        BatchRenderer();
        void setTextureId(GLuint textureId);
        GLuint getTextureId();
        void addMesh(Mesh mesh);
        void flush(World& world);
    private:
        std::vector<Mesh> meshDrawList;
        GLuint textureId;

        Buffer<GLfloat> squareVBO, attributeVBO, matrixVBO;
        Buffer<GLushort> squareEBO;

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

        int maxSize {65536};
    };
}

#endif // BATCH_RENDERER_H
