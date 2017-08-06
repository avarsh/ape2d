#include <ape/graphics/window.h>

namespace ape {

    /*
     * If the Fullscreen mode is activated then no other mode is allowed.
     * All Buttons takes precedence over close, maximize, minimize.
     * If either of the Close, Maximize or Minimize buttons are enabled
     * on their own, then it disables the others until they are also added.
     */
    int WindowMode::WINDOWED             = 1;
    int WindowMode::FULLSCREEN           = 2;
    int WindowMode::WINDOWED_FULLSCREEN  = 3;

    Window::Window() { }

    // Available window functions are described in detail here:
    // http://www.glfw.org/docs/latest/window_guide.html
    // They need to be exposed in the interface

    void Window::create(int width, int height, std::string title) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        // TODO: allow for window creation hints
        //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        dimensions = Vec2i(width, height);

        // Create the window
        window = glfwCreateWindow(dimensions.x, dimensions.y, title.c_str(),
                                  nullptr, nullptr);

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

    void Window::setVerticalSync(bool setting) {
        int interval = setting ? 1 : 0;
        glfwSwapInterval(interval);
    }

    void Window::clear(Color backgroundColor) {
        glClearColor(backgroundColor.red, backgroundColor.green,
                     backgroundColor.blue, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::display() {
        glfwSwapBuffers(window);
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
