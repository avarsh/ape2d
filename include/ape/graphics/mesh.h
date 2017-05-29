#ifndef MESH_H
#define MESH_H

#include <ape/ecs/component.h>
#include <ape/graphics/vertex.h>
#include <ape/graphics/vertex_attributes.h>

#include <vector>

namespace ape {

    struct Mesh : public Component<Mesh> {
        std::vector<Vertex> vertices;
        std::vector<GLushort> indices;

        int vertexAttributes { VERTEX_POSITION | VERTEX_COLOR };

        Vec2f origin;
    };
}

#endif // MESH_H
