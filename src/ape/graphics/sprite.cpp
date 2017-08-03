#include <ape/graphics/sprite.h>

namespace ape {
    void Sprite::setTextureID(int ID, TextureStore& textureStore) {
        textureID = ID;
        size = textureStore.getTexture(ID)->getSize();
    }

    int Sprite::getTextureID() {
        return textureID;
    }

    Vec2f Sprite::getSize() {
        return size;
    }

    void Sprite::setSize(Vec2f newSize) {
        size = newSize;
    }

    void Sprite::scaleBy(Vec2f scaleFactor) {
        size = size * scaleFactor;
    }

    void Sprite::scaleBy(float scaleFactor) {
        size = size * scaleFactor;
    }
}
