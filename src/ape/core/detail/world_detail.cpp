#include <ape/core/detail/world_detail.h>
#include <iostream>

#ifndef NDEBUG
#define ASSERT_MSG(condition, message) \
    do { \
        if(!(condition)) {\
            std::cerr << "Assertion `" #condition "` failed in ! " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while(false)
#else
#define ASSERT_MSG(condition, message) do {} while(false)
#endif

namespace ape {
    namespace world {
        namespace detail {

            std::unordered_map<std::string, int> tagKeys;
            int tagCounter = 1;
            std::vector<EntityData> entityData;
            entity_t counter = 1;
            std::queue<entity_t> freeList;
            std::queue<entity_t> killList;
            std::unordered_map<int, std::set<int>> exclusiveComponents;
            std::unordered_map<int, std::unique_ptr<ape::detail::BaseComponent>> componentInstances;
            // std::unordered_map<std::type_index, int> componentTypeMap;
            int currentBitsize = 1;
            std::vector<std::function<void(entity_t)>> initiationFuncs;
            std::vector<std::function<void(entity_t)>> blueprints;

            void assertEntity(entity_t entity, std::string caller) {
                std::string msg = "(assertion called by " + caller + ")";
                ASSERT_MSG(entity < counter, msg.c_str());
                ASSERT_MSG(entity > ENTITY_INVALID, msg.c_str());
                ASSERT_MSG(entityData[entity - 1].alive, msg.c_str());
            }

            void assertExclusive(entity_t entity, int componentHandle) {

                bool isExclusive = false;

                for(int i = 1; i < detail::currentBitsize; i = i << 1) {
                    // Check if the entity has that component type
                    // and if it is exclusive to the specified component
                    if((entityData[entity - 1].mask&i) == i &&
                       exclusiveComponents[componentHandle].count(i) == 1 &&
                       i != componentHandle) {
                           isExclusive = true;
                    }
                }

                assert(!isExclusive);
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
