#include <ape/graphics/sprite.h>

namespace ape {
    void Sprite::setTextureID(int ID, TextureStore& textureStore) {
        textureID = ID;
        size = textureStore.getTexture(ID)->getSize();
    }

    int Sprite::getTextureID() {
        return textureID;
    }

    Vec2i Sprite::getSize() {
        return size;
    }
}
