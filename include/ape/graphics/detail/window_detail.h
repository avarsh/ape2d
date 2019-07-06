#ifndef APE_WINDOW_DETAIL_H
#define APE_WINDOW_DETAIL_H

#include <SDL2/SDL.h>
#include <ape/core/vec2.h>

namespace ape {
    namespace window {
        namespace detail {
            extern SDL_Window *window;
            extern SDL_Renderer *renderer;
            extern Vec2i dims;
        }
    }
}

#endif