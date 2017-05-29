#include <ape/graphics/window.h>

namespace ape {

    void Window::create(int width, int height, std::string title) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        dimensions = Vec2i(width, height);

        // Create the window
        window = glfwCreateWindow(dimensions.x, dimensions.y, title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(window);
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        glfwSwapInterval(0); // Turn off vsync by default

        // Set the viewport to be the same size as the window initially
        int viewWidth, viewHeight;
        glfwGetFramebufferSize(window, &viewWidth, &viewHeight);

        resizedEvent.emit(Vec2i(viewWidth, viewHeight));
    }

    // TODO: capture an attempt at the window closing in an event, by using
    // glfwSetWindowCloseCallback
    bool Window::isOpen() {
        return !glfwWindowShouldClose(window);
    }

    void Window::clear(Color color) {
        glClearColor(color.red, color.green, color.blue, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::display() {
        glfwSwapBuffers(window);
    }

    void Window::destroy() {
        if(window != nullptr) {
            glfwDestroyWindow(window);
        }
    }
}
