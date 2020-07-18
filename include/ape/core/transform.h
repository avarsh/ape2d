#ifndef APE_TRANSFORM_H
#define APE_TRANSFORM_H

#include <ape/core/vec.h>

namespace ape {
    struct Transform {
        Vec2f position;
        Mat2f rotation;
    };
}

#endif