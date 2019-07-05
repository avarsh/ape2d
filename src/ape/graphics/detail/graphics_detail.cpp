#include <ape/graphics/detail/graphics_detail.h>
#include <iostream>

namespace ape {
    namespace graphics {
        namespace detail {
            void init() {
                if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                    std::cout << "SDL could not be initialized! SDL_Error: " 
                              << SDL_GetError() << std::endl;
                }
            }
        }
    }
}