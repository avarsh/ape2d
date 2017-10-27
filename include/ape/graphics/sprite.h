#ifndef SPRITE_H
#define SPRITE_H

#include <ape/core/world.h>
#include <ape/graphics/texture_store.h>
#include <ape/core/rect.h>

namespace ape {

    class Sprite : public Component<Sprite> {
    public:

        Sprite(entity_t entity) :
            Component<Sprite>(entity) { }
        Sprite(entity_t entity, int textureID) :
            Component<Sprite>(entity)
            { setTextureID(textureID); }

        void setTextureID(int ID);
        int getTextureID();

        Vec2f getSize();

        void setSize(Vec2f newSize);

        void scaleBy(Vec2f scaleFactor);
        void scaleBy(float scaleFactor);

        void setSubRect(float left, float top, float width, float height);
        FloatRect getSubRect();
        FloatRect getNormalizedSubRect();
    private:
        int textureID;
        //Vec2f size;
        Vec2f textureSize;
        Vec2f scaleFactor {Vec2f(1.0f, 1.0f)};

        FloatRect subRect;
        FloatRect normalizedRect;
    };
}

#endif // SPRITE_H
