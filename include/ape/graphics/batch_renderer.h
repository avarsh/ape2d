#ifndef BATCH_RENDERER_H
#define BATCH_RENDERER_H

#include <vector>
#include <ape/core/world.h>
#include <ape/graphics/mesh.h>
#include <ape/graphics/buffer.h>

namespace ape {
    class BatchRenderer {
    public:
        BatchRenderer(GLuint textureId);
        GLuint getTextureId();
        void addMesh(Mesh mesh);
        void drawAll(World& world, Buffer<GLfloat>& attributeVBO, Buffer<GLfloat>& matrixVBO);
        int getMeshListSize();
    private:
        std::vector<Mesh> meshDrawList;
        GLuint textureId;
    };
}

#endif // BATCH_RENDERER_H
