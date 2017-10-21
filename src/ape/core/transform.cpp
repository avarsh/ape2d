#include <ape/core/transform.h>

namespace ape {

    void Transform::setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }

    void Transform::setPosition(Vec2f newPosition) {
        position = newPosition;
    }

    Vec2f Transform::getPosition() {
        return position;
    }

    void Transform::move(float deltaX, float deltaY) {
        position += Vec2f(deltaX, deltaY);
    }

    void Transform::move(Vec2f delta) {
        position += delta;
    }

    void Transform::setRotation(float rotation) {
        this->rotation = rotation;
    }

    float Transform::getRotation() {
        return rotation;
    }

    Vec2f Transform::getVelocity() {
        return velocity;
    }

    void Transform::setVelocity(float velX, float velY) {
        velocity = Vec2f(velX, velY);
    }
}
