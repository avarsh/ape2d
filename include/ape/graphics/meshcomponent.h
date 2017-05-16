#include <glad/glad.h>
#include <ape/ecs/component.h>
#include <vector>

namespace ape {

    struct Mesh : public ape::Component<Mesh> {
        int mVertexCount {0};
        int mDataSize {5};

        int mIndexCount {0};

        std::vector<GLfloat> mVertices;
        std::vector<GLushort> mIndices;

        int mBufferIndex {-1}; // Will be used later when we have more than 1 buffer
    };
}
