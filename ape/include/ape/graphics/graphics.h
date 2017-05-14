#ifndef GRAPHICS_H 
#define GRAPHICS_H 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

#include <ape/graphics/shader.h>

namespace ape {

    class Graphics {
        public:
            Graphics();
            ~Graphics();

            void createWindow(unsigned int width, unsigned int height, const std::string& title);

            void clearWindow(float red=0.f, float green=0.f, float blue=0.f, float alpha=1.f);

            void displayWindow();

            bool windowIsOpen();
        private:
            GLFWwindow* mWindow {nullptr};

            static void _errorCallback(int error, const char* description) {
                std::cout << "Error " << error << " occured within GLFW: " << description << "\n";
            }
    };
}

#endif // GRAPHICS_H 
