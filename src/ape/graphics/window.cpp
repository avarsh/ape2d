#include <ape/graphics/window.h>
#include <ape/graphics/detail/window_detail.h>
#include <iostream>

#include <SDL2/SDL_image.h>

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
                /* TODO: Upon failure, abort and clean up all resources */
            } else {
                detail::renderer = SDL_CreateRenderer(detail::window, -1, SDL_RENDERER_ACCELERATED);
                if (detail::renderer == nullptr) {
                    std::cout << "Renderer could not be created. SDL_Error: "
                              << SDL_GetError() << std::endl;
                    
                    /* TODO: Upon failure, abort and clean up all resources */
                } else {
                    SDL_SetRenderDrawColor(detail::renderer, 0xFF, 0xFF, 0xFF, 0xFF ); 

                    /* TODO: Allow more image types */
                    int flags = IMG_INIT_PNG;
                    if (!(IMG_Init(flags) & flags)) {
                        std::cout << "PNG loading could not be initialized. SDL_Error: "
                                  << SDL_GetError() << std::endl;
                        /* TODO: Upon failure, abort and clean up all resources */
                    }
                }

                /* TODO: window creation event */
            }
        }

        void clear(Color color) {
            SDL_SetRenderDrawColor(detail::renderer, color.red, color.green, color.blue, color.alpha);
            SDL_RenderClear(detail::renderer);
        }

        void display() {
            SDL_RenderPresent(detail::renderer);
        }

        void destroy() {
            if (detail::window != nullptr) {
                SDL_DestroyWindow(detail::window);
                detail::window = nullptr;
            }
        }
    }
}