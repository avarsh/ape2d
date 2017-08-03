#ifndef SPRITE_H
#define SPRITE_H

#include <ape/core/world.h>
#include <ape/graphics/texture_store.h>

namespace ape {

    class Sprite : public Component<Sprite> {
    public:
        void setTextureID(int ID, TextureStore& textureStore);
        int getTextureID();

        Vec2f getSize();

        void setSize(Vec2f newSize);

        void scaleBy(Vec2f scaleFactor);
        void scaleBy(float scaleFactor);
    private:
        int textureID;
        Vec2f size;
    };
}

#endif // SPRITE_H
