#include <ape/core/transform.h>

namespace ape {

    void Transform::setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }

    Vec2f Transform::getPosition() {
        return position;
    }

    void Transform::move(float deltaX, float deltaY) {
        position += Vec2f(deltaX, deltaY);
    }

    void Transform::setRotation(float rotation) {
        this->rotation = rotation;
    }

    float Transform::getRotation() {
        return rotation;
    }
}