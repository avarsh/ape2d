#ifndef SPRITE_H
#define SPRITE_H

#include <ape/core/world.h>
#include <ape/graphics/texture_store.h>

namespace ape {

    class Sprite : public Component<Sprite> {
    public:
        void setTextureID(int ID, TextureStore& textureStore);
        int getTextureID();

        Vec2i getSize();
    private:
        int textureID;
        Vec2i size;
    };
}

#endif // SPRITE_H
