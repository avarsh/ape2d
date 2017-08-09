#include <ape/graphics/shader.h>

#include <fstream>
#include <iostream>
#include <sstream>

namespace ape {
    void Shader::load(const std::string& vertexFile, const std::string& fragmentFile) {

        int vertexIndex = 0;
        int fragmentIndex = 1;

        std::string fileStrings[2];
        std::ifstream shaderFiles[2];

        for(auto& file : shaderFiles) {
           file.exceptions(std::ifstream::badbit);
        }

        try {
            std::stringstream shaderStreams[2];
            for(int index = 0; index < 2; index++) {
                if(index == 0) {
                    shaderFiles[index].open(vertexFile);
                } else {
                    shaderFiles[index].open(fragmentFile);
                }

                shaderStreams[index] << shaderFiles[index].rdbuf();
                shaderFiles[index].close();

                fileStrings[index] = shaderStreams[index].str();

            }

        } catch (std::ifstream::failure err) {
            std::cout << "Error: Shader file not successfully read!" << std::endl;
        }

        const GLchar* shaderCodes[2];
        GLuint shaders[2];

        program = glCreateProgram();

        GLint success;
        GLchar infoLog[512];

        for(int index = 0; index < 2; index++) {
            shaderCodes[index] = fileStrings[index].c_str();

            // Compile the shaders

            GLenum shaderEnum = (index == vertexIndex) ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
            shaders[index] = glCreateShader(shaderEnum);
            glShaderSource(shaders[index], 1, &shaderCodes[index], nullptr);
            glCompileShader(shaders[index]);

            glGetShaderiv(shaders[index], GL_COMPILE_STATUS, &success);
            if(!success) {
                glGetShaderInfoLog(shaders[index], 512, nullptr, infoLog);
                std::string shaderType = (index == vertexIndex) ? "Vertex" : "Fragment";
                std::cout << "Error: " << shaderType << " Shader compilation failed.\n" <<
                    infoLog << std::endl;
            }

            glAttachShader(program, shaders[index]);
        }

        glLinkProgram(program);

        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            std::cout << "Error: Program linking failed.\n" << infoLog << std::endl;
        }

        glDeleteShader(shaders[0]);
        glDeleteShader(shaders[1]);
    }

    GLuint Shader::getProgram() {
        return program;
    }

    void Shader::use() {
        glUseProgram(program);
    }

    int Shader::getUniformLocation(const std::string& uniformName) {
        return glGetUniformLocation(program, uniformName.c_str());
    }

    void Shader::setUniformInt(const std::string& uniformName, int value) {
        int loc = glGetUniformLocation(program, uniformName.c_str());
        glUniform1i(loc, value);
    }
}
