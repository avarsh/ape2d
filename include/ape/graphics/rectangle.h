#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <ape/graphics/vertex.h>
#include <ape/ecs/component.h>

namespace ape {

    struct RectangleShape : public Component<RectangleShape> {
        RectangleShape() {  }
        RectangleShape(float left, float top, float width, float height) {
            vertices[0].position.x = left;
            vertices[0].position.y = top;

            vertices[1].position.x = left + width;
            vertices[1].position.y = top;

            vertices[2].position.x = left + width;
            vertices[2].position.y = top + height;

            vertices[3].position.x = left;
            vertices[3].position.y = top + height;
        }

        Vertex vertices[4];
    };
}

#endif // RECTANGLE_H
