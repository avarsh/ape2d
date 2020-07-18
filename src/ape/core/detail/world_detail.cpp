#include <ape/core/detail/world_detail.h>

namespace ape::world::detail {
    std::queue<entity_t> _freeList;
    std::queue<entity_t> _killList;
    entity_t _entityCounter = ape::null;

    void _update() {
        while(!_killList.empty()) {
            // Logic to destroy entity

            _killList.pop();
        }
    }
}