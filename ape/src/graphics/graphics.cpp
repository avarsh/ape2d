#include <ape/graphics/graphics.h>

namespace ape {
    Graphics::Graphics() {
        // Initialise glfw
        if(!glfwInit()) {
            std::cout << "GLFW failed to initalise.\n";
        }

        glfwSetErrorCallback(_errorCallback);
    }

    Graphics::~Graphics() {
        glfwDestroyWindow(mWindow);
        glfwTerminate();
    }

    void Graphics::createWindow(unsigned int width, unsigned int height, const std::string& title) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        mWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(mWindow);
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        glfwSwapInterval(1);

        int w, h;
        glfwGetFramebufferSize(mWindow, &w, &h);
        glViewport(0, 0, w, h);
 
    }

    void Graphics::clearWindow(float red, float green, float blue, float alpha) {
        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Graphics::displayWindow() {
        glfwSwapBuffers(mWindow);
    }

    bool Graphics::windowIsOpen() {
        return !glfwWindowShouldClose(mWindow);
    }
}
