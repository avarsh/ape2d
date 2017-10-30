#ifndef WORLD_DETAIL_H
#define WORLD_DETAIL_H

#include <unordered_map>
#include <queue>
#include <memory>
#include <set>
#include <typeindex>
#include <functional>
#include <ape/core/defines.h>
#include <ape/core/component.h>
#include <ape/core/detail/component_detail.h>

namespace ape {
    namespace world {
        namespace detail {

            /*
             * A custom component, used to store strings, or "tags".
             */
            struct TagComponent : public Component<TagComponent> {
                TagComponent(entity_t entity) : Component<TagComponent>(entity) { }

                std::unordered_map<int, std::string> tags;
            };

            // Used to keep track of tags and to look them up quickly in tag components.
            extern std::unordered_map<std::string, int> tagKeys;

            // Used to assign a unique key to each tag.
            extern int tagCounter;

            /*
             * Gets the key value for a tag - the key value is then used
             * to lookup the tag in the tag component.
             */
            int getTagKey(std::string tag);

            /*
             * A structure to store data about an entity, such as where its
             * components are in their pools, a bitmask to indicate what
             * components it has and a boolean flag to mark it as alive.
             */
            struct EntityData {
                std::unordered_map<int, int> indices;
                int mask {0};
                bool alive {true};

                entity_t next { ENTITY_INVALID };
                entity_t previous { ENTITY_INVALID };
            };

            // Data for each entity in the world
            extern std::vector<EntityData> entityData;

            // Used to allocate new entities - note that entities cannot
            // have a handle of 0. This is useful when checking certain
            // parameters.
            extern entity_t counter;

            // The queue of entities which have recently been deleted
            extern std::queue<entity_t> freeList;

            // The queue of entities which have recently been deleted
            extern std::queue<entity_t> killList;

            // The world keeps an instance of every component which is created.
            // This is done to access static members such as the component managers.
            extern std::unordered_map<int, std::unique_ptr<ape::detail::BaseComponent>> componentInstances;

            // We can map types to integer handles for components. This is mainly
            // used to build bitmasks for entities

            //yextern std::unordered_map<std::type_index, int> componentTypeMap;

            // The current bitsize, shifted left by 1 for every component.
            // Note that components cannot have a handle of 0.
            extern int currentBitsize;

            // Functions applied to every entity upon creation - usually used
            // to add components by default.
            extern std::vector<std::function<void(entity_t)>> initiationFuncs;

            // Blueprint related data
            extern std::vector<std::function<void(entity_t)>> blueprints;

            extern std::unordered_map<int, std::set<int>> exclusiveComponents;

            /*
             * Compile time assert to check if component class is of the
             * correct type.
             */
            template<class DerivedComponent>
            void staticAssertBase() {
                static_assert(std::is_base_of<ape::detail::BaseComponent, DerivedComponent>::value,
                             "Template parameter does not derive from base component class");
            }

            void assertExclusive(entity_t entity, int componentHandle);

            /*
             * Checks whether an entity is valid.
             */
            void assertEntity(entity_t entity);
        }
    }
}

#endif // WORLD_DETAIL_H
