#ifndef SPRITE_H
#define SPRITE_H

#include <ape/core/world.h>

namespace ape {

    // We have to forward declare this because the material class
    // contains the renderer class which in turn uses the sprite
    // class to display stuff, so if we include the material class here
    // then we get a circular inclusion loop. Since the sprite class
    // doesn't actually need to know anything about the material, merely
    // return a pointer to it, we can just declare it here.
    class Material;

    class Sprite : public Component<Sprite> {
    public:
        void setMaterial(Material* material);

        Material* getMaterial();
    private:
        Material* material;
    };
}

#endif // SPRITE_H
