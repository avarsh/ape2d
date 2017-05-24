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

            void initBuffers();
            void flush (World& world);
            void deleteBuffers();

            int getVertexCount();
            void setVertexCount(int vertexCount);

            int getElementCount();
            void setElementCount(int elementCount);
        private:
            GLuint vertexBuffer;
            GLuint indexBuffer;

            int vertexCount {0};
            int elementCount {0};

            int dataSize {5};
    };
}

#endif // BUFFER_H
