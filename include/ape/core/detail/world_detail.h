#ifndef APE_WORLD_DETAIL_H
#define APE_WORLD_DETAIL_H

#include <ape/core/common.h>

#include <queue>

namespace ape::world::detail {
    extern std::queue<entity_t> _freeList;
    extern std::queue<entity_t> _killList;
    extern entity_t _entityCounter;

    void _update();
}

#endif