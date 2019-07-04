#ifndef APE_WORLD_DETAIL_H
#define APE_WORLD_DETAIL_H

#include <queue>
#include <vector>
#include <functional>
#include <unordered_map>
#include <ape/core/constants.h>

namespace ape {
    namespace world {
        namespace detail {

            /*
             * A structure to store data about an entity, such as where its
             * components are in their pools, a bitmask to indicate what
             * components it has and a boolean flag to mark it as alive.
             */
            struct EntityData {
                // Stores component indices in respective pools
                std::unordered_map<int, int> indices;
                uint32_t mask {0};
                bool alive {true};
                uint32_t version {0};
            };

            // Data for each entity in the world
            extern std::vector<EntityData> entityData;

            // Queue of entities which have been destroyed from the world
            extern std::queue<entity_t> freeList;

            // Queue of entities which have been deleted but not freed
            extern std::queue<entity_t> killList;
            
            // Used to allocate new entities - note that entities cannot
            // have a handle of 0. This is useful when checking certain
            // parameters.
            extern entity_t entityCounter;

            extern std::vector<std::function<void(entity_t)>> blueprints;

            /*
             * Compile time assert to check if component class is of the
             * correct type.
             */
            template<class DerivedComponent>
            void staticAssertBase() {
                static_assert(std::is_base_of<ape::detail::BaseComponent, DerivedComponent>::value,
                             "Template parameter does not derive from base component class");
            }

            /*
             * Checks whether an entity is valid.
             */
            void assertEntity(entity_t entity, std::string caller);
        }
    }
}


#endif // APE_WORLD_DETAIL_H