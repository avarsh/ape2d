#ifndef APE_RECT_DETAIL_H
#define APE_RECT_DETAIL_H

#include <SDL2/SDL_rect.h>
#include <ape/core/rect.h>

namespace ape {
    namespace detail {
        /*
         * Converts an ape::IntRect into an SDL_Rect.
         */
        SDL_Rect convertRect(IntRect& rect);
    }
}

#endif