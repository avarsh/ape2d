#ifndef BUFFER_H
#define BUFFER_H

#include <glad/glad.h>
#include <vector>

#include <ape/ecs/world.h>
#include <ape/graphics/meshcomponent.h>
#include <ape/utils/vector.h>

namespace ape {
    class Buffer {
        public:
            Buffer();

            void initBuffers(GLuint vertexArray);

            void updateBuffer(World& world);

            void deleteBuffers();

            int mVertexCount {0};
            int mElementCount {0};

            int mDataSize {5};
        private:
            GLuint mVertexBuffer;
            GLuint mIndexBuffer;
    };
}

#endif // BUFFER_H
