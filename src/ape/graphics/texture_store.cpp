#include <ape/graphics/texture_store.h>
#include <ape/graphics/detail/window_detail.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cassert>

namespace ape {

    texture_id_t TEXTURE_INVALID = -1;

    texture_id_t TextureStore::loadTexture(const std::string& source) {
        SDL_Surface *surface = IMG_Load(source.c_str());
        if (surface == NULL) {
            std::cout << "Cannot load image from source: " << source
                      << " - IMG_Error: " << IMG_GetError() << std::endl;
            return TEXTURE_INVALID;
        } else {
            SDL_Texture *texturePtr = SDL_CreateTextureFromSurface(window::detail::renderer, surface);
            if (!texturePtr) {
                std::cout << "Unable to create texture from source: " << source 
                          << " - SDL_Error: " << SDL_GetError() << std::endl;
                SDL_FreeSurface(surface);
                return TEXTURE_INVALID;
            }

            texture_id_t id = textures.size();
            textures.push_back(texturePtr);
            textureLoaded.emit(id);
            return id;
        }

        return TEXTURE_INVALID;
    }

    Vec2i TextureStore::getTextureSize(texture_id_t id) {
        assert(id >= 0 && id < textures.size());
        Vec2i dims;
        SDL_QueryTexture(textures[id], NULL, NULL, &dims.x, &dims.y);
        return dims;
    }

    SDL_Texture* TextureStore::getTexture(texture_id_t id) {
        assert(id >= 0 && id < textures.size());
        return textures[id];
    }

    void TextureStore::freeTextures() {
        for (SDL_Texture* texturePtr : textures) {
            SDL_DestroyTexture(texturePtr);
        }
    }

    Event<texture_id_t> TextureStore::textureLoaded;
    std::vector<SDL_Texture*> TextureStore::textures;
    
}