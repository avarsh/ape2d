#ifndef APE_SPRITE_H
#define APE_SPRITE_H

#include <ape/core/component.h>
#include <SDL2/SDL.h>

namespace ape {
    class Sprite : public Component<Sprite> {
    public:
        Sprite(entity_t entity) : Component<Sprite>(entity) { }
    private:
        SDL_Texture *texture;
    };
}

#endif 