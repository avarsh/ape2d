#ifndef APE_SCENE_DETAIL_H
#define APE_SCENE_DETAIL_H

#include <ape/core/constants.h>
#include <ape/scene/node.h>


namespace ape {
    namespace scene {
        namespace detail {
            void init();
            void render();
            void traverse(const entity_t entity);
        }
    }
}

#endif
