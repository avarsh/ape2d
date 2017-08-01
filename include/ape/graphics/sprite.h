#ifndef SPRITE_H
#define SPRITE_H

#include <ape/core/world.h>
#include <ape/graphics/texture_store.h>

namespace ape {

    class Sprite : public Component<Sprite> {
    public:
        void setTextureID(int ID);
        int getTextureID();
    private:
        int textureID;
    };
}

#endif // SPRITE_H
