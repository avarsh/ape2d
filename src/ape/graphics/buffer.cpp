#include <ape/graphics/buffer.h>

namespace ape {

    Buffer::Buffer() {

    }

    void Buffer::initBuffers() {

        // Generate the buffers
        glGenBuffers(1, &vertexBuffer);
        glGenBuffers(1, &indexBuffer);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, 65536, NULL, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 65536, NULL, GL_DYNAMIC_DRAW);
    }

    void Buffer::updateBuffer(World& world) {

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

        GLfloat *vertPointer = (GLfloat*)glMapBufferRange(GL_ARRAY_BUFFER, 0,
            vertexCount * dataSize, GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

        GLushort *indexPointer = (GLushort*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0,
            elementCount, GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

        assert(vertPointer != NULL);
        assert(indexPointer != NULL);

        int vertIndex = 0;
        int indicesIndex = 0;

        int vertexCount = 0;

        for(auto& mesh : world.getComponentList<Mesh>()) {
            const auto& vertices = mesh.vertices;
            const auto& indices = mesh.indices;

            for(int vertex = 0; vertex < vertices.size(); vertex++) {
                vertPointer[vertIndex + (vertex * mesh.dataSize)] = vertices[vertex].position.x;
                vertPointer[vertIndex + (vertex * mesh.dataSize) + 1] = vertices[vertex].position.y;
                vertPointer[vertIndex + (vertex * mesh.dataSize) + 2] = vertices[vertex].colors.red;
                vertPointer[vertIndex + (vertex * mesh.dataSize) + 3] = vertices[vertex].colors.green;
                vertPointer[vertIndex + (vertex * mesh.dataSize) + 4] = vertices[vertex].colors.blue;
            }

            for(int offset = 0; offset < indices.size(); offset++) {
                indexPointer[indicesIndex + offset] = indices[offset] + vertexCount;
            }

            vertIndex += (vertices.size() * mesh.dataSize);

            indicesIndex += indices.size();

            vertexCount += mesh.vertices.size();
        }

        glUnmapBuffer(GL_ARRAY_BUFFER);
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    }

    void Buffer::deleteBuffers() {
        glDeleteBuffers(1, &vertexBuffer);
        glDeleteBuffers(1, &indexBuffer);
    }
}
