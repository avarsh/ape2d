#ifndef APE_WINDOW_H
#define APE_WINDOW_H

#include <SDL2/SDL.h>
#include <string>
#include <ape/graphics/color.h>
#include <ape/graphics/sprite.h>
#include <ape/core/event.h>
#include <ape/core/transform.h>

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
         * Clears the window background colour.
         * @param color The colour to set the background to.
         */
        void clear(Color color = Color(0, 0, 0));

        /**
         * Renders a sprite to the screen.
         * @param sprite The sprite component to render.
         */
        void draw(Sprite& sprite, Transform& transform);

        /**
         * Displays any rendered entities in the window.
         */
        void display();

        /**
         * Destroys the window.
         */
        void destroy();

        /**
         * Event which is emitted when the window is first created.
         */
        extern Event<Vec2i> windowCreated;

        /**
         * Event which is queued when the window is resized.
         */
        extern Event<Vec2i> windowResized;

        /**
         * Event which is queued when the window is closed.
         */
        extern Event<> windowClosed;
    }
}

#endif 