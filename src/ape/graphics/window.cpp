#include <ape/graphics/window.h>

namespace ape {
    namespace window {

        Event<Vec2i> createdEvent;

        void create(int width, int height, std::string title) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            // TODO: allow for window creation hints
            //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

            detail::dimensions = Vec2i(width, height);

            // Create the window
            detail::window = glfwCreateWindow(detail::dimensions.x,
                                      detail::dimensions.y, title.c_str(),
                                      nullptr, nullptr);

            glfwMakeContextCurrent(detail::window);
            gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

            glfwSwapInterval(0); // Turn off vsync by default

            // Set the viewport to be the same size as the window initially
            int viewWidth, viewHeight;
            glfwGetFramebufferSize(detail::window, &viewWidth, &viewHeight);

            createdEvent.emit(Vec2i(viewWidth, viewHeight));
        }

        // TODO: capture an attempt at the window closing in an event, by using
        // glfwSetWindowCloseCallback
        bool isOpen() {
            return !glfwWindowShouldClose(detail::window);
        }

        void setTitle(const std::string& title) {
            glfwSetWindowTitle(detail::window, title.c_str());
        }

        void setVerticalSync(bool setting) {
            int interval = setting ? 1 : 0;
            glfwSwapInterval(interval);
        }

        void clear(Color backgroundColor) {
            glClearColor(backgroundColor.red, backgroundColor.green,
                         backgroundColor.blue, 1.f);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void display() {
            glfwSwapBuffers(detail::window);
        }

        void destroy() {
            if(detail::window != nullptr) {
                glfwDestroyWindow(detail::window);
            }
        }
    }
}
