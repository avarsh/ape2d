#ifndef APE_WORLD_H
#define APE_WORLD_H

#include <ape/core/common.h>
#include <ape/core/detail/world_detail.h>

namespace ape::world {
    /**
     * Creates a new entity.
     * @return The entity, represented by a 32 bit integer.
     */
    entity_t createEntity();

    /**
     * Creates a new entity.
     * @param The entity to delete, represented by a 32 bit integer.
     */
    void deleteEntity(entity_t entity);
}

#endif