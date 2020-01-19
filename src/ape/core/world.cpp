#include <ape/core/world.h>
#include <cassert>

namespace ape {
    namespace world {
        
        Event<entity_t> entityDeleted;

        entity_t createEntity() {
            entity_t entity;

            if (detail::freeList.size() > 0) {
                entity = detail::freeList.front();
                detail::freeList.pop();

                assert(entity != ENTITY_INVALID);

                detail::getData(entity).alive = true;
                detail::getData(entity).version++;
            } else {
                entity = detail::entityCounter++;
                detail::entityData.push_back(detail::EntityData());
            }

            for (const auto& func : detail::initiationFuncs) {
                func(entity);
            }

            return entity;            
        }

        entity_t createEntityFromBlueprint(blueprint_t blueprint) {
            assert(blueprint < detail::blueprints.size());
            
            entity_t entity = createEntity();

            //detail::blueprints[blueprint]
            /* TODO: Rest of this function */

            return entity;
        }

        void deleteEntity(entity_t entity) {
            detail::assertEntity(entity, "world::deleteComponent");
            entityDeleted.emit(entity);
            detail::killList.push(entity);
        }

        void refresh() {
            while (detail::killList.size() > 0) {
                auto entity = detail::killList.front();
                auto& data = detail::getData(entity);

                data.alive = false;

                // Iterate over every component type
                for (int i = 1; i < detail::currentBitsize; i++){
                    // Check that the entity has that component
                    if ((data.mask & i) == i) {
                        int index = data.indices[i];
                        entity_t toUpdate = detail::componentInstances[i]->detach(index);

                        if (toUpdate != ENTITY_INVALID) {
                            data.indices[i] = index;
                        }
                    }
                }

                // Remove the entity from all tags
                for (int tag : data.tags) {
                    // Find the tag mapping and remove the entity
                    if (detail::tagMapping.find(tag) != detail::tagMapping.end()) { 
                        detail::tagMapping[tag].erase(entity);
                    }
                }

                data.tags.clear();

                detail::getData(entity).mask = 0;
                detail::freeList.push(entity);
                detail::killList.pop();
            }
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

        entity_t getFirstEntity() {
            entity_t first = 0;
            while (first == ENTITY_INVALID) {
                first = getNext(first);
            }

            return first;
        }

        void tagEntity(entity_t entity, int tag) {
            detail::tagMapping[tag].insert(entity);
            detail::getData(entity).tags.insert(tag);
        }

        const std::set<entity_t>& getEntitiesWithTag(int tag) {
            return detail::tagMapping[tag];
        }
    }
    
}