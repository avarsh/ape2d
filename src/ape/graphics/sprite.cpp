#include <ape/graphics/sprite.h>

namespace ape {
    void Sprite::setMaterial(Material* material) {
        this->material = material;
    }

    Material* Sprite::getMaterial() {
        return material;
    }
}
