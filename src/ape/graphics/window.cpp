#include <ape/graphics/window.h>

namespace ape {

    Window::Window() { }

    // Available window functions are described in detail here:
    // http://www.glfw.org/docs/latest/window_guide.html
    // They need to be exposed in the interface

    void Window::create(int width, int height, std::string title) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        // TODO: allow for window creation hints
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

        createdEvent.emit(Vec2i(viewWidth, viewHeight));
    }

    // TODO: capture an attempt at the window closing in an event, by using
    // glfwSetWindowCloseCallback
    bool Window::isOpen() {
        return !glfwWindowShouldClose(window);
    }

    void Window::setTitle(const std::string& title) {
        glfwSetWindowTitle(window, title.c_str());
    }

    GLFWwindow* Window::getWindow() {
        return window;
    }

    void Window::destroy() {
        if(window != nullptr) {
            glfwDestroyWindow(window);
        }
    }
}
