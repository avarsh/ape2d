#ifndef APE_TRANSFORM_H
#define APE_TRANSFORM_H

#include <ape/core/component.h>
#include <ape/core/vec2.h>

namespace ape {
    struct Transform : Component<Transform> {
        Transform(entity_t entity) : Component<Transform>(entity) {}

        Vec2f position;
        Vec2f velocity;
        float rotation {0.f};
    }
}

#endif 