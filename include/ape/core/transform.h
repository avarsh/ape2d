#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <ape/ecs/component.h>
#include <ape/utils/vector.h>

namespace ape {
    struct Transform : public Component<Transform> {
        Vec2f position;
        Vec2f velocity;

        float rotation {0.f};
    };
}

#endif // TRANSFORM_H
