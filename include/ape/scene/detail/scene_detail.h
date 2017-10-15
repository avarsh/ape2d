#ifndef SCENE_DETAIL_H
#define SCENE_DETAIL_H

#include <ape/core/world.h>
#include <ape/scene/node.h>
#include <ape/graphics/graphics.h>

namespace ape {
    namespace scene {
        namespace detail {
            void traverse(entity_t entity);
        }
    }
}

#endif // SCENE_DETAIL_H
