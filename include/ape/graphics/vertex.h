#ifndef VERTEX_H
#define VERTEX_H

#include <ape/graphics/color.h>
#include <ape/graphics/vec2glf.h>

namespace ape {
    struct Vertex {
        Vec2GLf position;
        Vec2GLf texture;
        Color color;
    };
}

#endif // VERTEX_H
