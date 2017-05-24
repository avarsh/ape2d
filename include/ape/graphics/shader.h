#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ape {

    class Shader {
        public:
            void loadShaders(const std::string& vertexFile, const std::string& fragmentFile);
            void useShader();
        private:
            GLuint mProgram;
    };
}

#endif // SHADER_H
