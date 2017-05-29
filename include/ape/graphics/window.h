#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include <ape/utils/event.h>
#include <ape/graphics/color.h>
#include <ape/utils/vector.h>

namespace ape {

    class Window {
    public:
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
         * Clears the window to a specified color.
         * @param color The color to clear the window to.
         */
        void clear(Color color);

        /**
         * Displays the window, swapping buffers and rendering all meshes.
         */
        void display();

        void destroy();

        Event<Vec2i> resizedEvent;
    private:
        GLFWwindow* window {nullptr};
        Vec2i dimensions;
    };
}

#endif // WINDOW_H
