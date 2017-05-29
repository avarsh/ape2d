#ifndef BUFFER_H
#define BUFFER_H

#include <glad/glad.h>
#include <ape/graphics/vertex_attributes.h>
#include <ape/graphics/mesh.h>
#include <iostream>

namespace ape {

    template<typename DataType>
    class Buffer {
    public:
        void init(GLenum type, GLvoid* data, int size, bool dynamic) {
            bufferType = type;

            glGenBuffers(1, &bufferID);
            bind();

            GLenum usage = dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
            glBufferData(bufferType, size, data, usage);
        }

        void bind() {
            glBindBuffer(bufferType, bufferID);
        }

        GLuint getID() {
            return bufferID;
        }

        void deleteBuffer() {
            glDeleteBuffers(1, &bufferID);
        }

    private:
        GLuint bufferID;
        GLenum bufferType;
    };
}

#endif // BUFFER_H
