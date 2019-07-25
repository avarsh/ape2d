#ifndef APE_WORLD_DETAIL_H
#define APE_WORLD_DETAIL_H

#include <queue>
#include <vector>
#include <functional>
#include <unordered_map>
#include <memory>
#include <cassert>
#include <ape/core/constants.h>
#include <ape/core/component.h>

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
            
            /* Used to allocate new entities - note that entities cannot
             * have a handle of 0. This is useful when checking certain
             * parameters.
             */
            extern entity_t entityCounter;

            // The world keeps an instance of every component which is created.
            // This is done to access static members such as the component pools.
            extern std::unordered_map<int, std::unique_ptr<ape::detail::BaseComponent>> componentInstances;

            extern std::vector<std::function<void(entity_t)>> blueprints;
            extern std::vector<std::function<void(entity_t)>> initiationFuncs;

            // The current bitsize, shifted left by 1 for every component.
            // Note that components cannot have a handle of 0.
            extern int currentBitsize;

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
             * Retrieves data struct for entity.
             */
            EntityData& getData(entity_t entity);

            /*
             * Checks whether an entity is valid.
             */
            void assertEntity(entity_t entity, std::string caller);
        }
    }
}


#endif