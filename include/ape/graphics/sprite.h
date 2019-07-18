#ifndef APE_SPRITE_H
#define APE_SPRITE_H

#include <ape/core/component.h>
#include <SDL2/SDL.h>
#include <ape/graphics/texture_store.h>
#include <ape/core/rect.h>

namespace ape {
    /**
     * Sprite component for sprites. Holds a texture id and information
     * on how to process the texture.
     */
    class Sprite : public Component<Sprite> {
    public:
        Sprite(entity_t entity);

        texture_id_t textureId;
        IntRect textureRect;
    };
}

#endif 