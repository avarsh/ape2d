#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>

namespace ape {
    class Shader {
    public:
        void load(const std::string& vertexFile, const std::string& fragmentFile);
        GLuint getProgram();
        void use();

        int getUniformLocation(const std::string& uniformName);
    private:
        GLuint program;
    };
}

#endif // SHADER_H
