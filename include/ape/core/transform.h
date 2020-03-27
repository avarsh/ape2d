#ifndef APE_TRANSFORM_H
#define APE_TRANSFORM_H

#include <ape/core/component.h>
#include <ape/core/vec2.h>

namespace ape {
    struct Transform : Component<Transform> {
        Transform(entity_t entity) : Component<Transform>(entity) {}

        Transform(const Transform& other) : Component<Transform>(other.entity) { 
            position = other.position;
            velocity = other.velocity;
            accel = other.accel;
            rotation = other.rotation;
            scale = other.scale;
        }

        Transform& operator=(const Transform& other) {
            entity = other.entity;
            position = other.position;
            velocity = other.velocity;
            accel = other.accel;
            rotation = other.rotation;
            scale = other.scale;

            return *this;
        };

        Vec2f position;
        Vec2f velocity;
        Vec2f accel;
        float rotation {0.f};
        float scale {1.0f};
    };
}

#endif 