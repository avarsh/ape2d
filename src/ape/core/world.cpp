#include <ape/core/world.h>

namespace ape::world {

    using namespace detail;

    entity_t createEntity() {
        if (!_freeList.empty()) {
            entity_t entity = _freeList.front();
            _freeList.pop();
            return entity;
        }

        return ++_entityCounter;
    }

    void deleteEntity(entity_t entity) {
        _killList.push(entity);
    }
}