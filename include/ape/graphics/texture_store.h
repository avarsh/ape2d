#ifndef APE_TEXTURE_STORE_H
#define APE_TEXTURE_STORE_H

#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>

namespace ape {

    using texture_id_t = uint32_t;
    extern texture_id_t TEXTURE_INVALID;

    /**
     * Loads and stores textures.
     */
    class TextureStore {
    public:
        /**
         * Loads a texture at a given path.
         * @param source The string file path.
         * @return An id for the texture.
         */
        static texture_id_t loadTexture(const std::string& source);

        /**
         * Frees all textures.
         */
        static void freeTextures();

        /**
         * Retrieves a pointer to a texture given an id.
         * @param id The id of the texture
         * @return A smart pointer to the texture.
         */
        static std::unique_ptr<SDL_Texture>& getTexture(texture_id_t id);
    private:
        static std::vector<std::unique_ptr<SDL_Texture>> textures;
    };
}

#endif