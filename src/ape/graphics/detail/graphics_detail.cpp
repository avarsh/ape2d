#include <ape/graphics/detail/graphics_detail.h>
#include <ape/graphics/window.h>
#include <iostream>
#include <SDL2/SDL_hints.h>

namespace ape {
    namespace graphics {
        namespace detail {
            void init() {
                if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                    std::cout << "SDL could not be initialized! SDL_Error: " 
                              << SDL_GetError() << std::endl;
                }

                /* TODO: Remember that if the user wants to have custom
                   OpenGL calls then they need to call SDL_RenderFlush. We
                   should expose this call somehow. */
                SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");
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