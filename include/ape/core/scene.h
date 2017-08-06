#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#include <ape/core/world.h>
#include <ape/core/node.h>
#include <ape/graphics/graphics.h>

namespace ape {
    class Scene {
    public:
        Scene(World& world);
        void init();
        void traverse(Graphics& graphics);

        static entity_t rootNode;
    private:
        World& world;

        void _traverse(entity_t entity, Graphics& graphics);
    };
}

#endif // SCENE_GRAPH_H
