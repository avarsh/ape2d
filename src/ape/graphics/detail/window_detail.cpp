#include <ape/graphics/detail/window_detail.h>

namespace ape {
    namespace window {
        namespace detail {
            SDL_Window *window = nullptr;
            SDL_Surface *surface = nullptr;
            Vec2i dims;
        }
    }
}