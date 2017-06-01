#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <ape/core/component.h>
#include <ape/core/vec2.h>

namespace ape {
    struct Transform : public Component<Transform> {
        Vec2f position;
        Vec2f velocity;

        // TODO: some games might not require elements to be rotated.
        // In this case, we can save matrix calculations by allowing an
        // engine setting which disregards this value.

        float rotation {0.f};
    };
}

#endif // TRANSFORM_H
