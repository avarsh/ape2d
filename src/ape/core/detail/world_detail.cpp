#include <ape/core/detail/world_detail.h>

namespace ape {
    namespace world {
        namespace detail {

            std::unordered_map<std::string, int> tagKeys;
            int tagCounter = 1;
            std::vector<EntityData> entityData;
            entity_t counter = 1;
            std::queue<entity_t> freeList;
            std::queue<entity_t> killList;
            std::unordered_map<int, std::unique_ptr<ape::detail::BaseComponent>> componentInstances;
            // std::unordered_map<std::type_index, int> componentTypeMap;
            int currentBitsize = 1;
            std::function<void(entity_t)> initiationFunc = [](entity_t e) {};
            std::vector<std::function<void(entity_t)>> blueprints;

            void assertEntity(entity_t entity) {
                assert(entity < counter);
                assert(entity > ENTITY_INVALID);
                assert(entityData[entity - 1].alive);
            }

            // Look at getComponentHandle for an explanation on how this works
            int getTagKey(std::string tag) {
                int& key = tagKeys[tag];
                if(key) return key;
                key = tagCounter;
                tagCounter++;
                return key;
            }
        }
    }
}
