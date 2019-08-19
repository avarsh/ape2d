#include <ape/core/detail/rect_detail.h>

namespace ape {
    namespace detail {
        SDL_Rect convertRect(IntRect& rect) {
            SDL_Rect converted;
            converted.x = rect.origin.x;
            converted.y = rect.origin.y;
            converted.w = rect.size.x;
            converted.h = rect.size.y;

            return converted;
        }
    }
}