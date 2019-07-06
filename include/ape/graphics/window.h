#ifndef APE_WINDOW_H
#define APE_WINDOW_H

#include <SDL2/SDL.h>
#include <string>
#include <ape/graphics/color.h>

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
         * Displays any rendered entities in the window.
         */
        void display();

        /**
         * Destroys the window.
         */
        void destroy();
    }
}

#endif 