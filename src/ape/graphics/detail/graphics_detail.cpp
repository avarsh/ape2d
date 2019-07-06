#include <ape/graphics/detail/graphics_detail.h>
#include <ape/graphics/window.h>
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

            void pushRendererColor(SDL_Renderer *renderer) {
                Color color;
                SDL_GetRenderDrawColor(renderer, &color.red, &color.green, &color.blue,  &color.alpha);
                rendererColStack.push_front(color);
            }

            void popRendererColor(SDL_Renderer *renderer) {
                Color color = rendererColStack.front();
                SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
                rendererColStack.pop_front();
            }

            void destroy() {
                window::destroy();
                SDL_Quit();
            }

            std::deque<Color> rendererColStack;
        }
    }
}