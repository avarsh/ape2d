#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ape/graphics/detail/window_detail.h>

#include <string>
#include <ape/core/event.h>
#include <ape/graphics/color.h>
#include <ape/core/vec2.h>

namespace ape {
    namespace window {
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
         * Enables or disables vertical sync, also known as v-sync.
         * @param setting Boolean dictating if it is on or off.
         */
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
         * Event emitted when the window is resized.
         */
        extern Event<Vec2i> resizedEvent;

        /**
         * Event emitted when the window is first created.
         */
        extern Event<Vec2i> createdEvent;
    }
}

#endif // WINDOW_H
