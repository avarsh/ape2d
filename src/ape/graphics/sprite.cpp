#include <ape/graphics/sprite.h>

namespace ape {
    void Sprite::setTextureID(int ID) {
        this->textureID = ID;
    }

    int Sprite::getTextureID() {
        return textureID;
    }
}
