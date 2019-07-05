#ifndef APE_WINDOW_H
#define APE_WINDOW_H

#include <SDL2/SDL.h>
#include <string>

namespace ape {
    namespace window {
        /**
         * Initializes the main window.
         * @param width  The width of the window.
         * @param height The height of the window.
         * @param title  The string which will be the title of the window.
         */
        void create(int width, int height, std::string title);
    }
}

#endif 