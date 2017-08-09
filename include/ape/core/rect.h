#ifndef RECT_H
#define RECT_H

#include <ape/core/vec2.h>

namespace ape {

    template <class T>
    class Rect {
    public:
        Rect() {
            origin = Vec2<T>();
            size = Vec2<T>();
        }

        Rect(T left, T top, T width, T height) {
            origin = Vec2<T>(left, top);
            size = Vec2<T>(width, height);
        }

        Vec2<T> origin, size;
    };

    using IntRect = Rect<int>;
    using FloatRect = Rect<float>;
}

#endif // RECT_H
