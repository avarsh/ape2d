#include <ape/graphics/texture_store.h>
#include <ape/graphics/detail/window_detail.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cassert>

namespace ape {

    texture_id_t TEXTURE_INVALID = 0;

    texture_id_t TextureStore::loadTexture(const std::string& source) {
        SDL_Surface *surface = IMG_Load(source.c_str());
        if (surface == NULL) {
            std::cout << "Cannot load image from source: " << source
                      << " - SDL_Error: " << IMG_GetError() << std::endl;
            return TEXTURE_INVALID;
        } else {
            std::unique_ptr<SDL_Texture> texturePtr = std::make_unique<SDL_Texture>(
                SDL_CreateTextureFromSurface(window::detail::renderer, surface));
            if (!texturePtr) {
                std::cout << "Unable to create texture from source: " << source 
                          << " - SDL_Error: " << SDL_GetError() << std::endl;
                SDL_FreeSurface(surface);
                return TEXTURE_INVALID;
            }

            textures.push_back(texturePtr);
            /* TODO: Texture load event */
            return textures.size();
        }

        return TEXTURE_INVALID;
    }

    std::unique_ptr<SDL_Texture>& TextureStore::getTexture(texture_id_t id) {
        assert(id > 0 && id <= textures.size());
        return textures[id - 1];
    }

    void TextureStore::freeTextures() {
        for (auto& texturePtr : textures) {
            SDL_DestroyTexture(texturePtr.get());
        }
    }

    
}