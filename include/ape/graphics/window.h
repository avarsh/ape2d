#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include <ape/core/event.h>
#include <ape/graphics/color.h>
#include <ape/core/vec2.h>

namespace ape {

    struct WindowMode {
        static int WINDOWED;
        static int FULLSCREEN;
        static int WINDOWED_FULLSCREEN;
    };

    class Window {
    public:
        Window();

        Window(const Window& other) = delete;
        void operator=(const Window &other) = delete;

        /**
         * Initializes the main window.
         * @param width  The width of the window.
         * @param height The height of the window.
         * @param title  The string which will be the title of the window.
         */
        void create(int width, int height, std::string title);

        /**
         * Checks whether the window is still open.
         * @return A boolean value indicating if the window is open.
         */
        bool isOpen();

        /**
         * Sets the title of the window.
         * @param title The string to be set as the title.
         */
        void setTitle(const std::string& title);

        void setVerticalSync(bool setting);

        /**
         * Clears the window background colour.
         * @param backgroundColor The colour to set the background to.
         */
        void clear(Color backgroundColor = Color(0, 0, 0));

        /**
         * Swaps the buffers so that any rendered entities are displayed.
         */
        void display();

        /**
         * Destroys the window.
         */
        void destroy();

        /**
         * Gets the actual GLFW window pointer - only for internal/testing
         * purposes.
         * @return A pointer to a GLFWwindow instance
         */
        GLFWwindow* getWindow();

        /**
         * Event emitted when the window is resized.
         */
        Event<Vec2i> resizedEvent;

        /**
         * Event emitted when the window is first created.
         */
        Event<Vec2i> createdEvent;
    private:
        GLFWwindow* window {nullptr};
        Vec2i dimensions;

        friend class Engine;
    };
}

#endif // WINDOW_H
