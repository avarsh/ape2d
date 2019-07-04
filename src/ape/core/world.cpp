#include <ape/core/world.h>
#include <cassert>

namespace ape {
    namespace world {
        
        entity_t createEntity() {
            entity_t entity;

            if (detail::freeList.size() > 0) {
                entity = detail::freeList.front();
                detail::freeList.pop();

                assert(entity != ENTITY_INVALID);

                detail::entityData[entity - 1].alive = true;
                detail::entityData[entity - 1].version++;
            } else {
                entity = detail::entityCounter++;
                detail::entityData.push_back(detail::EntityData());
            }

            /* TODO: Initialisation functions */

            return entity;            
        }

        entity_t createEntityFromBlueprint(blueprint_t blueprint) {
            assert(blueprint < detail::blueprints.size());
            
            entity_t entity = createEntity();

            //detail::blueprints[blueprint]
        }

        entity_t getNext(entity_t current) {
            bool nextIsAlive = false;
            entity_t next = ENTITY_INVALID;
            while(!nextIsAlive) {
                if (current == detail::entityData.size()) {
                    nextIsAlive = true;
                } else {
                    current++;
                    if (detail::entityData[current - 1].alive) {
                        next = current;
                        nextIsAlive = true;
                    }
                }
            }

            return next;
        }
    }
    
}