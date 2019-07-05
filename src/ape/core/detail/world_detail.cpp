#include <ape/core/detail/world_detail.h>
#include <ape/core/debug.h>

namespace ape {
    namespace world {
        namespace detail {
            std::vector<EntityData> entityData;

            std::queue<entity_t> freeList;
            std::queue<entity_t> killList;
            std::vector<std::function<void(entity_t)>> blueprints;
            std::unordered_map<int, std::unique_ptr<ape::detail::BaseComponent>> componentInstances;

            entity_t entityCounter = 1;
            int currentBitsize = 1;

            EntityData& getData(entity_t entity) {
                return entityData[entity - 1];
            }

            void assertEntity(entity_t entity, std::string caller) {
                std::string msg = "(assertion called by " + caller + ")";
                ASSERT_MSG(entity < entityCounter, msg.c_str());
                ASSERT_MSG(entity > ENTITY_INVALID, msg.c_str());
                ASSERT_MSG(entityData[entity - 1].alive, msg.c_str());
            }
        }
    }
}