#include <ape/core/world.h>

namespace ape {
    namespace world {

        Event<entity_t> entityDeleted;

        entity_t createEntity() {
            if(detail::freeList.size() > 0) {
                entity_t entity = detail::freeList.front();
                detail::freeList.pop();

                detail::entityData[entity - 1].alive = true;
                detail::entityData[entity - 1].next = getNext(entity);
                for(const auto& func : detail::initiationFuncs) {
                    func(entity);
                }

                return entity;
            }

            entity_t entity = detail::counter++;

            detail::entityData.push_back(detail::EntityData());
            for(const auto& func : detail::initiationFuncs) {
                func(entity);
            }
            detail::entityData[entity - 1].next = getNext(entity);

            return entity;
        }

        bool entityIsAlive(entity_t entity) {
            return detail::entityData[entity - 1].alive;
        }

        entity_t createEntityFromBlueprint(int blueprint) {
            assert(blueprint < detail::blueprints.size());
            entity_t newEntity = createEntity();

            detail::blueprints[blueprint](newEntity);

            return newEntity;
        }

        void deleteEntity(entity_t entity) {
            detail::assertEntity(entity, "world::deleteComponent");
            entityDeleted.emit(entity);
            detail::killList.push(entity);
        }

        void refresh() {
            while(detail::killList.size() > 0) {
                auto entity = detail::killList.front();

                detail::entityData[entity - 1].alive = false;

                entity_t prev = detail::entityData[entity - 1].previous;
                entity_t next = detail::entityData[entity - 1].next;

                if(prev != ENTITY_INVALID) {
                    detail::entityData[prev - 1].next = next;
                }

                if(next != ENTITY_INVALID) {
                    detail::entityData[next - 1].previous = prev;
                }

                // Iterate over every component type
                for(int i = 1; i < detail::currentBitsize; i = i << 1) {
                    // Check if the entity has that component type
                    if((detail::entityData[entity - 1].mask&i) == i) {
                        // If it does, find out where it is located
                        int index = detail::entityData[entity - 1].indices[i];
                        entity_t entityToUpdate = detail::componentInstances[i]->remove(index);

                        if(entityToUpdate != ENTITY_INVALID) {
                            detail::entityData[entityToUpdate - 1].indices[i] = index;
                        }
                    }
                }

                detail::entityData[entity - 1].mask = 0;
                detail::freeList.push(entity);

                detail::killList.pop();
            }
        }

        entity_t getFirstEntity() {
            return getNext(ENTITY_INVALID);
        }

        entity_t getNext(entity_t currentEntity) {
            bool nextIsAlive = false;
            entity_t nextAlive = ENTITY_INVALID;
            while(!nextIsAlive) {
                if(currentEntity == detail::entityData.size()) {
                    nextIsAlive = true;
                } else {
                    currentEntity++;
                    if(detail::entityData[currentEntity - 1].alive) {
                        nextAlive = currentEntity;
                        nextIsAlive = true;
                    }
                }
            }

            return nextAlive;
        }

        void addTag(entity_t entity, std::string tag) {
            if(!entityHasComponent<detail::TagComponent>(entity)) {
                addComponent<detail::TagComponent>(entity);
            }

            int tagKey = detail::getTagKey(tag);
            getComponent<detail::TagComponent>(entity).tags[tagKey] = tag;
        }

        std::vector<entity_t> getTaggedEntities(std::string tag) {
            std::vector<entity_t> entities;
            int tagKey = detail::getTagKey(tag);
            for(auto& tagComponent : getComponentList<detail::TagComponent>()) {
                if(tagComponent.tags.find(tagKey) != tagComponent.tags.end()) {
                    entities.push_back(tagComponent.getEntity());
                }
            }

            return entities;
        }

        bool entityHasTag(entity_t entity, std::string tag) {
            if(!entityHasComponent<detail::TagComponent>(entity)) {
                return false;
            }

            int tagKey = detail::getTagKey(tag);
            auto& tagComponent = getComponent<detail::TagComponent>(entity);
            if(tagComponent.tags.find(tagKey) == tagComponent.tags.end()) {
                return false;
            }

            return true;
        }

    }
}
