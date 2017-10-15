#include <ape/graphics/sprite.h>

namespace ape {
    void Sprite::setTextureID(int ID) {
        textureID = ID;
        textureSize = textureStore::getTexture(ID)->getSize();
        setSubRect(0, 0, textureSize.x, textureSize.y);
    }

    int Sprite::getTextureID() {
        return textureID;
    }

    Vec2f Sprite::getSize() {
        return subRect.size * scaleFactor;
    }

    void Sprite::setSize(Vec2f newSize) {
        scaleFactor = newSize / subRect.size;
    }

    void Sprite::scaleBy(Vec2f scaleFactor) {
        this->scaleFactor = this->scaleFactor * scaleFactor;
    }

    void Sprite::scaleBy(float scaleFactor) {
        this->scaleFactor = this->scaleFactor * scaleFactor;
    }

    void Sprite::setSubRect(float left, float top, float width, float height) {
        subRect.origin = Vec2f(left, top);
        subRect.size = Vec2f(width, height);
        normalizedRect.origin = subRect.origin / textureSize;
        normalizedRect.size = subRect.size / textureSize;
    }

    FloatRect Sprite::getSubRect() {
        return subRect;
    }

    FloatRect Sprite::getNormalizedSubRect() {
        return normalizedRect;
    }
}
