#include <ape/core/world.h>

namespace ape {
    entity_t World::createEntity() {
        if(freeList.size() > 0) {
            entity_t entity = freeList.front();
            freeList.pop();

            entityData[entity - 1].alive = true;
            entityData[entity - 1].next = getNext(entity);
            initiationFunc(entity);

            return entity;
        }

        entity_t entity = counter++;

        entityData.push_back(EntityData());
        initiationFunc(entity);
        entityData[entity - 1].next = getNext(entity);

        return entity;
    }

    entity_t World::createEntityFromBlueprint(int blueprint) {
        assert(blueprint < blueprints.size());
        entity_t newEntity = createEntity();

        blueprints[blueprint](newEntity);

        return newEntity;
    }

    void World::deleteEntity(entity_t entity) {
        _assertEntity(entity);
        killList.push(entity);
    }

    void World::refresh() {
        while(killList.size() > 0) {
            auto entity = killList.front();

            entityData[entity - 1].alive = false;

            entity_t prev = entityData[entity - 1].previous;
            entity_t next = entityData[entity - 1].next;

            if(prev != ENTITY_INVALID) {
                entityData[prev - 1].next = next;
            }

            if(next != ENTITY_INVALID) {
                entityData[next - 1].previous = prev;
            }

            // Iterate over every component type
            for(int i = 1; i < currentBitsize; i = i << 1) {
                // Check if the entity has that component type
                if((entityData[entity - 1].mask&i) == i) {
                    // If it does, find out where it is located
                    int index = entityData[entity - 1].indices[i];
                    entity_t entityToUpdate = componentInstances[i]->remove(index);

                    if(entityToUpdate != ENTITY_INVALID) {
                        entityData[entityToUpdate - 1].indices[i] = index;
                    }
                }
            }

            entityData[entity - 1].mask = 0;
            freeList.push(entity);

            killList.pop();
        }
    }

    entity_t World::getFirstEntity() {
        return getNext(ENTITY_INVALID);
    }

    entity_t World::getNext(entity_t currentEntity) {
        bool nextIsAlive = false;
        entity_t nextAlive = ENTITY_INVALID;
        while(!nextIsAlive) {
            if(currentEntity == entityData.size()) {
                nextIsAlive = true;
            } else {
                currentEntity++;
                if(entityData[currentEntity - 1].alive) {
                    nextAlive = currentEntity;
                    nextIsAlive = true;
                }
            }
        }

        return nextAlive;
    }

    void World::addTag(entity_t entity, std::string tag) {
        if(!entityHasComponent<TagComponent>(entity)) {
            addComponent<TagComponent>(entity);
        }

        int tagKey = _getTagKey(tag);
        getComponent<TagComponent>(entity).tags[tagKey] = tag;
    }

    std::vector<entity_t> World::getTaggedEntities(std::string tag) {
        std::vector<entity_t> entities;
        int tagKey = _getTagKey(tag);
        for(auto& tagComponent : getComponentList<TagComponent>()) {
            if(tagComponent.tags.find(tagKey) != tagComponent.tags.end()) {
                entities.push_back(tagComponent.entity);
            }
        }

        return entities;
    }

    bool World::entityHasTag(entity_t entity, std::string tag) {
        if(!entityHasComponent<TagComponent>(entity)) {
            return false;
        }

        int tagKey = _getTagKey(tag);
        auto& tagComponent = getComponent<TagComponent>(entity);
        if(tagComponent.tags.find(tagKey) == tagComponent.tags.end()) {
            return false;
        }

        return true;
    }

    // Look at World::_getComponentHandle for an explanation on how this works
    int World::_getTagKey(std::string tag) {
        int& key = tagKeys[tag];
        if(key) return key;
        key = tagCounter;
        tagCounter++;
        return key;
    }

    void World::_assertEntity(entity_t entity) {
        assert(entity < counter);
        assert(entity > ENTITY_INVALID);
        assert(entityData[entity - 1].alive);
    }

}
