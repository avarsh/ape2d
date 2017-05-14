#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>    /* std::unordered_map */
#include <typeinfo>         /* typeid()           */
#include <typeindex>        /* std::type_index    */
#include <memory>           /* std::unique_ptr    */
#include <iostream>         /* std::cout          */
#include <queue>            /* std::queue         */
#include <functional>       /* std::function      */
#include <cassert>          /* assert()           */

#include <ape/ecs/defines.h>
#include <ape/ecs/component.h>
#include <ape/ecs/componentmanager.h>
#include <ape/utils/event.h>

namespace ape {

    /**
    * The world is a centralized data management class.
    *
    * The world manages the creation and lifetime of entities and allows
    * information about entities such as components to be retrieved.
    */
    class World {
        public:

            /**
             * Creates a new entity, or reassigns one which has been previously
             * deleted.
             *
             * @return The integer handle for the entity.
             */
            entity_t createEntity();

            /**
             * Creates a new entity from a predefined blueprint.
             * @param  blueprint The handle for the blueprint which will be used.
             * @return           The integer handle for the entity.
             */
            entity_t createEntityFromBlueprint(int blueprint);

            /**
             * Destroys an entity, deleting all attached components and marking
             * it as dead.
             *
             * @param entity The entity to be destroyed.
             */
            void deleteEntity(entity_t entity);

            /**
             * Allows an entity to be tagged with a string.
             * @param entity The entity to tag.
             * @param tag    The string to tag the entity with,
             */
            void addTag(entity_t entity, std::string tag);

            /**
             * Gets a list of entities with a certain tag.
             * @param tag The tag to search with.
             * @return A vector of entity handles.
             */
            std::vector<entity_t> getTaggedEntities(std::string tag);

            bool entityHasTag(entity_t entity, std::string tag);

            /**
             * Get the first alive entity.
             * @return The handle for the entity.
             */
            entity_t getFirstEntity();

            /**
             * Get the next alive entity after a given entity.
             * @param  currentEntity The entity to start from.
             * @return               The handle of the next alive entity.
             */
            entity_t getNext(entity_t currentEntity);

            void refresh();

            /**
             * Adds a specified component to the given entity.
             *
             * @tparam DerivedComponent The type of the component to add.
             * @param  entity           The entity to add the component to.
             */
            template<class DerivedComponent>
            DerivedComponent& addComponent(entity_t entity) {
                // TODO: Allow for the component to be initialized with variadic
                // parameters
                _staticAssertBase<DerivedComponent>();
                _assertEntity(entity);

                if(entityHasComponent<DerivedComponent>(entity)) {
                    return getComponent<DerivedComponent>(entity);
                }

                // We ask the manager to add the component...
                int index = DerivedComponent::mManager.addComponent(entity);
                // Then we store the index of the component within its pool
                // in a map.
                int cHandle = getComponentHandle<DerivedComponent>();
                mEntityData[entity - 1].mIndices[cHandle] = index;
                // Modify the mask to reflect that the entity has the component.
                mEntityData[entity - 1].mask |= cHandle;

                // We check whether we have an instance of the component added
                // to our map; otherwise, we create one.
                try {
                    mComponentInstances.at(cHandle);
                } catch (const std::out_of_range& error) {
                    mComponentInstances[cHandle] = std::make_unique<DerivedComponent>();
                }

                return getComponent<DerivedComponent>(entity);
            }

            /**
             * Adds a specified number of components to the given entity.
             * @tparam FirstComponent   The first component to add.
             * @tparam SecondComponent  The second component to add.
             * @tparam Remaining        A variadic template parameter, allowing any number of components to be added.
             * @param entity            The entity to add the components to.
             */
            template<class FirstComponent, class SecondComponent, class ...Remaining>
            void addComponents(entity_t entity) {
                addComponent<FirstComponent>(entity);
                addComponents<SecondComponent, Remaining...>(entity);
            }

            /**
             * An overload, allowing for a single component to be added, mainly
             * used as a method to stop recursion of the addComponents function.
             * @tparam FirstComponent The component to add.
             * @param entity          The entity to add the component to.
             */
            template<class FirstComponent>
            void addComponents(entity_t entity) {
                addComponent<FirstComponent>(entity);
            }

            /**
             * Removes a component from an entity.
             * @tparam DerivedComponent  The component type to remove.
             * @param entity             The entity to remove the component from.
             */
            template<class DerivedComponent>
            void removeComponent(entity_t entity) {
                _staticAssertBase<DerivedComponent>();
                _assertEntity(entity);
                assert(entityHasComponent<DerivedComponent>(entity));

                int handle = getComponentHandle<DerivedComponent>();
                int index = mEntityData[entity - 1].mIndices[handle];
                entity_t entityToUpdate = DerivedComponent::mManager.removeComponent(index);
                if(entityToUpdate != ENTITY_INVALID) {
                    mEntityData[entityToUpdate - 1].mIndices[handle] = index;
                }
            }

            /**
             * Removes a number of components from an entity.
             * @tparam FirstComponent   The first component to remove.
             * @tparam SecondComponent  The second component to remove.
             * @tparam Remaining        A variadic template parameter, allowing any number of components to be removed.
             * @param entity            The entity to remove the components from.
             */
            template<class FirstComponent, class SecondComponent, class ...Remaining>
            void removeComponents(entity_t entity) {
                removeComponent<FirstComponent>(entity);
                removeComponents<SecondComponent, Remaining...>(entity);
            }

            /**
             * An overload to remove a single component from an entity, used mainly
             * to stop the recursion of the main removeComponents function.
             * @tparam FirstComponent The component to remove.
             * @param entity          The entity to remove the component from.
             */
            template<class FirstComponent>
            void removeComponents(entity_t entity) {
                removeComponent<FirstComponent>(entity);
            }

            template<class DerivedComponent>
            void disableComponent(entity_t entity) {
                _staticAssertBase<DerivedComponent>();
                _assertEntity(entity);
                assert(entityHasComponent<DerivedComponent>(entity));

                int handle = getComponentHandle<DerivedComponent>();
                int index = mEntityData[entity - 1].mIndices[handle];
                DerivedComponent::mManager.setComponentEnabled(index, false);
            }

            template<class DerivedComponent>
            void enableComponent(entity_t entity) {
                _staticAssertBase<DerivedComponent>();
                _assertEntity(entity);
                assert(entityHasComponent<DerivedComponent>(entity));

                int handle = getComponentHandle<DerivedComponent>();
                int index = mEntityData[entity - 1].mIndices[handle];
                DerivedComponent::mManager.setComponentEnabled(index, true);
            }

            /**
             * Retrieve a component for a specified entity.
             * @tparam DerivedComponent The type of component to retrieve.
             * @param  entity           The entity to retrieve the component for.
             * @return                  A reference to the component.
             */
            template<class DerivedComponent>
            DerivedComponent& getComponent(entity_t entity) {
                _staticAssertBase<DerivedComponent>();
                _assertEntity(entity);
                assert(entityHasComponent<DerivedComponent>(entity));

                // Firstly get the mask for the component
                int mask = getComponentHandle<DerivedComponent>();
                // Retrieve the component's location within its pool using
                // our mappings
                int index = mEntityData[entity - 1].mIndices[mask];
                return getComponentList<DerivedComponent>()[index];
            }

            /**
             * A function to check whether an entity has a component attached.
             * @param  entity The handle of the entity to check.
             * @return        A boolean value indicating whether the entity holds the component.
             */
            template<class DerivedComponent>
            bool entityHasComponent(entity_t entity) {
                _staticAssertBase<DerivedComponent>();
                _assertEntity(entity);

                int cMask = getComponentHandle<DerivedComponent>();
                if((mEntityData[entity - 1].mask&cMask) == cMask) {
                    return true;
                }

                return false;
            }

            /**
             * A function to check whether an entity has any amount of components.
             * @param  entity           The handle of the entity to check.
             * @tparam FirstComponent   The first component to check for.
             * @tparam SecondComponent  The second component to check for.
             * @tparam Remaining        A variadic template parameter, allowing any number of components to be checked against.
             * @return                  A boolean value indicating whether the entity holds all the desired components.
             */
            template<class FirstComponent, class SecondComponent, class ...Remaining>
            bool entityHasComponents(entity_t entity) {
                if(!entityHasComponent<FirstComponent>(entity)) {
                    return false;
                }

                return entityHasComponents<SecondComponent, Remaining...>(entity);
            }

            /**
             * An overload, allowing for a single component to be checked
             * against, mainly used to end the recursion of the main checking function.
             * @param  entity The handle of the entity to check.
             * @return        A boolean value indicating whether the entity holds the component.
             */
            template<class FirstComponent>
            bool entityHasComponents(entity_t entity) {
                return entityHasComponent<FirstComponent>(entity);
            }

            /*
             * Gets the component handle for a given component. The handle is
             * a unique series of bits assigned to every component.
             */
            template<class Component>
            int getComponentHandle() {
                /*
                 * The [] operator automatically creates a new value using
                 * the default constructor. For an integer value, this default
                 * is 0.
                 */
                int& handle = mComponentTypeMap[typeid(Component)];

                /*
                 * If the handle is not 0 (component handles cannot be 0!),
                 * it can be returned. The expression will evaluate to true
                 * if the handle exists.
                 */
                if(handle) return handle;

                /*
                 * Otherwise, we construct a new handle
                 * Because we are using a reference, this will also modify
                 * the hashed value in the map.
                 */
                handle = currentBitsize;

                /*
                 * Shift it left by 1 so we can get a unique series of bits for
                 * each component
                 */
                currentBitsize = currentBitsize << 1;

                return handle;
            }

            /**
             * Gets a list of components for a component type.
             * @tparam  DerivedComponent  The component to get the list for.
             * @return                    A reference to the list.
             */
            template<class DerivedComponent>
            std::vector<DerivedComponent>& getComponentList() {
                _staticAssertBase<DerivedComponent>();

                // Basically a convenience wrapper
                return DerivedComponent::mManager.getComponentList();
            }

            /**
             * Allows a number of components to be added by default to any
             * entity.
             *
             * @tparam Components The component types to be added.
             */
            template<class ...Components>
            void setDefaultComponents() {
                mInitiationFunc = [this](entity_t entity) {
                    addComponents<Components...>(entity);
                };
            }

            /**
             * Registers a new blueprint with the world. Blueprints can be used
             * to quickly create entities which all have a common set of components.
             * @return The integer handle for the blueprint.
             */
            template<class ...Components>
            int addBlueprint() {
                // A blueprint is just a lambda which adds the components.
                mBlueprints.push_back([this](entity_t entity){
                    addComponents<Components...>(entity);
                });

                // The handle is the blueprint's index
                return mBlueprints.size() - 1;
            }

        private:

            /*
             * A structure to store data about an entity, such as where its
             * components are in their pools, a bitmask to indicate what
             * components it has and a boolean flag to mark it as alive.
             */
            struct EntityData {
                std::unordered_map<int, int> mIndices;
                int mask {0};
                bool alive {true};

                entity_t mNext { ENTITY_INVALID };
                entity_t mPrevious { ENTITY_INVALID };
            };

            /*
             * A custom component, used to store strings, or "tags".
             */
            struct TagComponent : public Component<TagComponent> {
                std::unordered_map<int, std::string> mTags;
            };

            // Used to keep track of tags and to look them up quickly in tag components.
            std::unordered_map<std::string, int> mTagKeys;

            // Used to assign a unique key to each tag.
            int mTagCounter {1};

            /*
             * Gets the key value for a tag - the key value is then used
             * to lookup the tag in the tag component.
             */
            int _getTagKey(std::string tag);

            

            /*
             * A convenience function used to check at compile time if a template
             * parameter is derived from the component base class.
             */

            template<class DerivedComponent>
            void _staticAssertBase() {
                static_assert(std::is_base_of<BaseComponent, DerivedComponent>::value,
                             "Template parameter does not derive from base component class");
            }

            /*
             * A convenience function used to check whether an entity is valid.
             */
            void _assertEntity(entity_t entity);

            // The data for each entity
            std::vector<EntityData> mEntityData;

            // Used to allocate new entities - note that entities cannot
            // have a handle of 0. This is useful when checking certain
            // parameters.
            entity_t mCounter {1};

            // The queue of entities which have recently been deleted
            std::queue<entity_t> mFreeList;

            // The queue of entities which have recently been deleted
            std::queue<entity_t> mKillList;

            // The world keeps an instance of every component which is created.
            // This is done to access static members such as the component managers.
            std::unordered_map<int, std::unique_ptr<BaseComponent>> mComponentInstances;

            // We can map types to integer handles for components. This is mainly
            // used to build bitmasks for entities
            std::unordered_map<std::type_index, int> mComponentTypeMap;

            // The current bitsize, shifted left by 1 for every component.
            // Note that components cannot have a handle of 0.
            int currentBitsize {1};

            // A function applied to every entity upon creation - usually used
            // to add components by default.
            std::function<void(entity_t)> mInitiationFunc { [](entity_t e) {} };

            // Blueprint related data
            std::vector<std::function<void(entity_t)>> mBlueprints;

            struct {
                Event<entity_t, int> componentAdded;
            } events;
    };
}

#endif // WORLD_H
