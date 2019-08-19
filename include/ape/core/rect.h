#ifndef APE_RECT_H
#define APE_RECT_H

#include <ape/core/vec2.h>

namespace ape {

    /**
     * A class holding a rectangle or bounding-box-like object. It has
     * a position (the top left vertex) and a size.
     */
    template <class T>
    struct Rect {
        /**
         * Default constructor, creates a rect at (0, 0) with 0 size.
         */
        Rect() {
            origin = Vec2<T>();
            size = Vec2<T>();
        }

        /* TODO: Copy constructors */

        /**
         * Creates a rect with specified position and size.
         * @param left   The x value for the position.
         * @param top    The y value for the position.
         * @param width  The width of the rect.
         * @param height The height of the rect.
         */
        Rect(T left, T top, T width, T height) {
            origin = Vec2<T>(left, top);
            size = Vec2<T>(width, height);
        }

        Rect(Vec2<T> origin, Vec2<T> size) : origin(origin), size(size) { }

        Vec2<T> origin, size;
    };

    using IntRect = Rect<int>;
    using FloatRect = Rect<float>;
}

#endif
