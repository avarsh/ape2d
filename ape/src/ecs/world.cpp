#include <ape/ecs/world.h>

namespace ape {
    entity_t World::createEntity() {
        if(mFreeList.size() > 0) {
            entity_t entity = mFreeList.front();
            mFreeList.pop();

            mEntityData[entity - 1].alive = true;
            mEntityData[entity - 1].mNext = getNext(entity);
            mInitiationFunc(entity);

            return entity;
        }

        entity_t entity = mCounter++;

        mEntityData.push_back(EntityData());
        mInitiationFunc(entity);
        mEntityData[entity - 1].mNext = getNext(entity);

        return entity;
    }

    entity_t World::createEntityFromBlueprint(int blueprint) {
        assert(blueprint < mBlueprints.size());
        entity_t newEntity = createEntity();

        mBlueprints[blueprint](newEntity);

        return newEntity;
    }

    void World::deleteEntity(entity_t entity) {
        _assertEntity(entity);
        mKillList.push(entity);
    }

    void World::refresh() {
        while(mKillList.size() > 0) {
            auto entity = mKillList.front();

            mEntityData[entity - 1].alive = false;

            entity_t prev = mEntityData[entity - 1].mPrevious;
            entity_t next = mEntityData[entity - 1].mNext;

            if(prev != ENTITY_INVALID) {
                mEntityData[prev - 1].mNext = next;
            }

            if(next != ENTITY_INVALID) {
                mEntityData[next - 1].mPrevious = prev;
            }

            // Iterate over every component type
            for(int i = 1; i < currentBitsize; i = i << 1) {
                // Check if the entity has that component type
                if((mEntityData[entity - 1].mask&i) == i) {
                    // If it does, find out where it is located
                    int index = mEntityData[entity - 1].mIndices[i];
                    entity_t entityToUpdate = mComponentInstances[i]->remove(index);

                    if(entityToUpdate != ENTITY_INVALID) {
                        mEntityData[entityToUpdate - 1].mIndices[i] = index;
                    }
                }
            }

            mEntityData[entity - 1].mask = 0;
            mFreeList.push(entity);

            mKillList.pop();
        }
    }

    entity_t World::getFirstEntity() {
        return getNext(ENTITY_INVALID);
    }

    entity_t World::getNext(entity_t currentEntity) {
        bool nextIsAlive = false;
        entity_t nextAlive = ENTITY_INVALID;
        while(!nextIsAlive) {
            if(currentEntity == mEntityData.size()) {
                nextIsAlive = true;
            }

            currentEntity++;
            if(mEntityData[currentEntity - 1].alive) {
                nextAlive = currentEntity;
                nextIsAlive = true;
            }
        }

        return nextAlive;
    }

    void World::addTag(entity_t entity, std::string tag) {
        if(!entityHasComponent<TagComponent>(entity)) {
            addComponent<TagComponent>(entity);
        }

        int tagKey = _getTagKey(tag);
        getComponent<TagComponent>(entity).mTags[tagKey] = tag;
    }

    std::vector<entity_t> World::getTaggedEntities(std::string tag) {
        std::vector<entity_t> entities;
        int tagKey = _getTagKey(tag);
        for(auto& tagComponent : getComponentList<TagComponent>()) {
            if(tagComponent.mTags.find(tagKey) != tagComponent.mTags.end()) {
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
        if(tagComponent.mTags.find(tagKey) == tagComponent.mTags.end()) {
            return false;
        }

        return true;
    }

    // Look at World::_getComponentHandle for an explanation on how this works
    int World::_getTagKey(std::string tag) {
        int& key = mTagKeys[tag];
        if(key) return key;
        key = mTagCounter;
        mTagCounter++;
        return key;
    }

    void World::_assertEntity(entity_t entity) {
        assert(entity < mCounter);
        assert(entity > ENTITY_INVALID);
        assert(mEntityData[entity - 1].alive);
    }

}
