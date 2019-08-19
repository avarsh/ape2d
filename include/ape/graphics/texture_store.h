#ifndef APE_TEXTURE_STORE_H
#define APE_TEXTURE_STORE_H

#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <ape/core/event.h>
#include <ape/core/vec2.h>

namespace ape {

    using texture_id_t = int32_t;
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
         * Retrieves the dimensions of a texture.
         * @param id The texture identifier.
         * @return A vector containing the dimensions.
         */
        static Vec2i getTextureSize(const texture_id_t id);

        /**
         * Frees all textures.
         */
        static void freeTextures();

        /**
         * Retrieves a pointer to a texture given an id.
         * @param id The id of the texture
         * @return A smart pointer to the texture.
         */
        static SDL_Texture* getTexture(texture_id_t id);

        static Event<texture_id_t> textureLoaded;
    private:
        static std::vector<SDL_Texture*> textures;
    };
}

#endif