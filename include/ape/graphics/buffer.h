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

            void updateBuffer(World& world);

            void deleteBuffers();

            int vertexCount {0};
            int elementCount {0};

            int dataSize {5};
        private:
            GLuint vertexBuffer;
            GLuint indexBuffer;
    };
}

#endif // BUFFER_H
