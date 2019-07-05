#include <ape/graphics/window.h>
#include <ape/graphics/detail/window_detail.h>

namespace ape {
    namespace window {
        void create(int width, int height, std::string title) {
            detail::dims = Vec2i(width, height);
            /* TODO: Allow flags to be changed? */
            detail::window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, 
                                              SDL_WINDOWPOS_CENTERED, detail::dims.x, 
                                              detail::dims.y, SDL_WINDOW_SHOWN);
            if (detail::window == nullptr) {
                std::cout << "Window could not be created. SDL_Error: " 
                          << SDL_GetError() << std::endl;
            } else {
                detail::surface = SDL_GetWindowSurface(detail::window);

                /* TODO: window creation event */
            }
        }
    }
}