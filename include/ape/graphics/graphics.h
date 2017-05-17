#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

#include <ape/graphics/shader.h>
#include <ape/graphics/buffer.h>

#include <ape/ecs/world.h>

namespace ape {

    class Graphics {
        public:
            Graphics(World& world);
            ~Graphics();

            void createWindow(unsigned int width, unsigned int height, const std::string& title);

            void clearWindow(float red=0.f, float green=0.f, float blue=0.f, float alpha=1.f);

            void displayWindow(World& world);

            bool windowIsOpen();

            void addVertex(entity_t entity, GLfloat x, GLfloat y, GLfloat red=1.0f, GLfloat green=1.0f, GLfloat blue=1.0f);

            void setVertexColour(entity_t entity, int vertex, GLfloat red, GLfloat blue, GLfloat green);

            void setVertexPosition(entity_t entity, int vertex, GLfloat x, GLfloat y);
        private:
            GLFWwindow* mWindow {nullptr};

            static void _errorCallback(int error, const char* description) {
                std::cout << "Error " << error << " occured within GLFW: " << description << "\n";
            }

            Shader mPolygonShader;

            GLuint mPolygonVertexArray;
            Buffer mPolygonBuffer;

            World& mWorld;
    };
}

#endif // GRAPHICS_H
