#include <ape/graphics/buffer.h>

namespace ape {

    Buffer::Buffer() {

    }

    void Buffer::initBuffers(GLuint vertexArray) {

        // Generate the buffers
        glGenBuffers(1, &mVertexBuffer);
        glGenBuffers(1, &mIndexBuffer);

        glBindVertexArray(vertexArray);

        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, 65536, NULL, GL_DYNAMIC_DRAW);

        // The position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        // The colour attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 65536, NULL, GL_DYNAMIC_DRAW);

        glBindVertexArray(0);

        // Unbind these after unbinding vertex array
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Buffer::updateBuffer(World& world) {

        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);

        GLfloat *vertPointer = (GLfloat*)glMapBufferRange(GL_ARRAY_BUFFER, 0,
            mVertexCount * mDataSize, GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

        GLushort *indexPointer = (GLushort*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0,
            mElementCount, GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

        assert(vertPointer != NULL);
        assert(indexPointer != NULL);

        int vertIndex = 0;
        int indicesIndex = 0;

        int vertexCount = 0;

        for(auto& mesh : world.getComponentList<Mesh>()) {
            auto vertices = mesh.mVertices;
            auto indices = mesh.mIndices;

            for(int offset = 0; offset < vertices.size(); offset++) {
                vertPointer[vertIndex + offset] = vertices[offset];
            }

            for(int offset = 0; offset < indices.size(); offset++) {
                indexPointer[indicesIndex + offset] = indices[offset] + vertexCount;
            }

            vertIndex += vertices.size();
            indicesIndex += indices.size();

            vertexCount += mesh.mVertexCount;
        }

        glUnmapBuffer(GL_ARRAY_BUFFER);
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    }

    void Buffer::deleteBuffers() {
        glDeleteBuffers(1, &mVertexBuffer);
        glDeleteBuffers(1, &mIndexBuffer);
    }
}
