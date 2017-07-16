#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <ape/core/component.h>
#include <ape/core/vec2.h>

namespace ape {
    class Transform : public Component<Transform> {
        public:

            /**
             * Sets the position of the entity.
             * @param x The new x position.
             * @param y The new y position.
             */
            void setPosition(float x, float y);

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
             * Sets the rotation of the entity.
             * @param rotation The angle in radians.
             */
            void setRotation(float rotation);

            /**
             * Gets the current rotation of the entity.
             * @return [description]
             */
            float getRotation();

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
