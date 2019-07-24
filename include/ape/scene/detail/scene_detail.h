#ifndef APE_SCENE_DETAIL_H
#define APE_SCENE_DETAIL_H

#include <ape/core/constants.h>

namespace ape {
    namespace scene {
        namespace detail {
            void init();
            void render();
            void traverse();

            extern entity_t ROOT_NODE;
        }
    }
}

#endif