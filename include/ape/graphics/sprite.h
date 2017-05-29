#ifndef SPRITE_H
#define SPRITE_H

#include <ape/ecs/component.h>
#include <ape/utils/vector.h>

namespace ape {
    struct Sprite : public Component<Sprite> {
        Vec2f dimensions;

        int batchID {-1};
    };
}

#endif // SPRITE_H
