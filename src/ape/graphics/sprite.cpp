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
        return Vec2f(float(subRect.size.x) * scaleFactor.x,
                     float(subRect.size.y) * scaleFactor.y);
    }

    void Sprite::setSize(Vec2f newSize) {
        scaleFactor = Vec2f(newSize.x / float(subRect.size.x),
                            newSize.y / float(subRect.size.y));
    }

    void Sprite::scaleBy(Vec2f scaleFactor) {
        this->scaleFactor = this->scaleFactor * scaleFactor;
    }

    void Sprite::scaleBy(float scaleFactor) {
        this->scaleFactor = this->scaleFactor * scaleFactor;
    }

    void Sprite::setSubRect(int left, int top, int width, int height) {
        subRect.origin = Vec2i(left, top);
        subRect.size = Vec2i(width, height);
        normalizedRect.origin = Vec2f(subRect.origin.x, subRect.origin.y) / textureSize;
        normalizedRect.size =  Vec2f(subRect.size.x, subRect.size.y) / textureSize;
    }

    void Sprite::setSubRect(IntRect subRect) {
        setSubRect(subRect.origin.x, subRect.origin.y,
                  subRect.size.x, subRect.size.y);
    }

    IntRect Sprite::getSubRect() {
        return subRect;
    }

    FloatRect Sprite::getNormalizedSubRect() {
        return normalizedRect;
    }
}
