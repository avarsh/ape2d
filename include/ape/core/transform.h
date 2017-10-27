#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <ape/core/component.h>
#include <ape/core/vec2.h>

namespace ape {
    class Transform : public Component<Transform> {
        public:

            Transform(entity_t entity) : Component<Transform>(entity) { }
            Transform(entity_t entity, float xPosition, float yPosition) :
                Component<Transform>(entity) {
                position = Vec2f(xPosition, yPosition);
            }
            Transform(entity_t entity, Vec2f initialPosition) :
                Component<Transform>(entity) {
                position = initialPosition;
            }

            /**
             * Sets the position of the entity.
             * @param x The new x position.
             * @param y The new y position.
             */
            void setPosition(float x, float y);

            /**
             * Sets the position of the entity.
             * @param newPosition The new position as a vector.
             */
            void setPosition(Vec2f newPosition);

            /**
             * Gets the position of the entity.
             * @return A Vec2f containing the position coordinates.
             */
            Vec2f getPosition();

            /**
             * Moves the entity's position.
             * @param deltaX The amount to move in the x-direction.
             * @param deltaY The amount to move in the y-direction.
             */
            void move(float deltaX, float deltaY);

            /**
             * Moves the entity's position.
             * @param delta The amount to move as a vector.
             */
            void move(Vec2f delta);

            /**
             * Sets the rotation of the entity.
             * @param rotation The angle in radians.
             */
            void setRotation(float rotation);

            /**
             * Gets the current rotation of the entity.
             * @return [description]
             */
            float getRotation();

            /**
             * Gets the entity's current velocity.
             * @return The velocity as a vector.
             */
            Vec2f getVelocity();

            /**
             * Sets the velocity of the entity.
             * @param velX The velocity in the x direction.
             * @param velY The velocity in the y direction.
             */
            void setVelocity(float velX, float velY);

            /**
             * Sets the velocity of the entity.
             * @param newVelocity The velocity as a vector.
             */
            void setVelocity(Vec2f newVelocity);

        private:
            Vec2f position;
            Vec2f velocity;

            // TODO: some games might not require elements to be rotated.
            // In this case, we can save matrix calculations by allowing an
            // engine setting which disregards this value.

            float rotation {0.f};
    };
}

#endif // TRANSFORM_H
