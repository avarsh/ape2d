#ifndef GRAPHICS_DETAIL_H
#define GRAPHICS_DETAIL_H

#include <SDL2/SDL.h>
#include <deque>
#include <ape/graphics/color.h>

namespace ape {
    namespace graphics {
        namespace detail {
            /**
             * Initializes the graphics system.
             */
            void init();

            /**
             * Saves the renderer color on to stack.
             */
            void pushRendererColor(SDL_Renderer *renderer);

            /**
             * Retrieves the renderer color from stack.
             */
            void popRendererColor(SDL_Renderer *renderer)

            /**
             *  Cleans up resources used by the graphics system.
             */
            void destroy();

            extern std::deque<Color> rendererColStack;
        }
    }
}

#endif