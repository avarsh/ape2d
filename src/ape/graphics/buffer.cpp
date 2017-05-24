#include <ape/graphics/buffer.h>

namespace ape {

    Buffer::Buffer() { }

    void Buffer::initBuffers() {
        // Generate the buffers
        glGenBuffers(1, &vertexBuffer);
        glGenBuffers(1, &indexBuffer);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, 65536, NULL, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 65536, NULL, GL_DYNAMIC_DRAW);
    }

    void Buffer::flush(World& world) {

        //std::cout << vertexCount * dataSize << ", " << elementCount << std::endl;

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

        GLfloat *vertPointer = (GLfloat*)glMapBufferRange(GL_ARRAY_BUFFER, 0,
            vertexCount * dataSize, GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

        GLushort *indexPointer = (GLushort*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0,
            elementCount, GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

        assert(vertPointer != NULL);
        assert(indexPointer != NULL);

        int dataIndex = 0;
        int indicesIndex = 0;
        int renderedVertices = 0;

        for(auto& mesh : world.getComponentList<Mesh>()) {
            const auto& vertices = mesh.vertices;
            const auto& indices = mesh.indices;

            for(int vertex = 0; vertex < vertices.size(); vertex++) {
                int offset = dataIndex + (vertex * this->dataSize);

                vertPointer[offset]     = vertices[vertex].position.x;
                vertPointer[offset + 1] = vertices[vertex].position.y;
                vertPointer[offset + 2] = vertices[vertex].color.red;
                vertPointer[offset + 3] = vertices[vertex].color.green;
                vertPointer[offset + 4] = vertices[vertex].color.blue;

                if((mesh.mask&VM_TEXTURE) == VM_TEXTURE) {
                    vertPointer[offset + 5] = vertices[vertex].texCoord.x;
                    vertPointer[offset + 6] = vertices[vertex].texCoord.y;
                }
            }

            for(int offset = 0; offset < indices.size(); offset++) {
                indexPointer[indicesIndex + offset] = indices[offset] + renderedVertices;
            }

            dataIndex += (vertices.size() * mesh.dataSize);
            indicesIndex += indices.size();
            renderedVertices += vertices.size();
        }

        glUnmapBuffer(GL_ARRAY_BUFFER);
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    }

    void Buffer::deleteBuffers() {
        glDeleteBuffers(1, &vertexBuffer);
        glDeleteBuffers(1, &indexBuffer);
    }

    int Buffer::getVertexCount() {
        return vertexCount;
    }

    void Buffer::setVertexCount(int vertexCount) {
        this->vertexCount = vertexCount;
    }

    int Buffer::getElementCount() {
        return elementCount;
    }

    void Buffer::setElementCount(int elementCount) {
        this->elementCount = elementCount;
    }
}
