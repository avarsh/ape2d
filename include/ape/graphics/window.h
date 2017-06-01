#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include <ape/core/event.h>
#include <ape/graphics/color.h>
#include <ape/core/vec2.h>

namespace ape {

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

        /**
         * Destroys the window.
         */
        void destroy();

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
    };
}

#endif // WINDOW_H
