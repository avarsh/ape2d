#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>    /* std::unordered_map */
#include <typeinfo>         /* typeid()           */
#include <typeindex>        /* std::type_index    */
#include <type_traits>
#include <memory>           /* std::unique_ptr    */
#include <iostream>         /* std::cout          */
#include <queue>            /* std::queue         */
#include <functional>       /* std::function      */
#include <cassert>          /* assert()           */
#include <utility>

#include <ape/core/defines.h>
#include <ape/core/component.h>
#include <ape/core/componentmanager.h>
#include <ape/core/event.h>

#include <ape/core/detail/world_detail.h>

namespace ape {

    /**
    * The world is a centralized data management class.
    *
    * The world manages the creation and lifetime of entities and allows
    * information about entities such as components to be retrieved.
    */
    namespace world {

        // Forward declarations
        template<class DerivedComponent>
        constexpr bool entityHasComponent(entity_t entity);

        template<class DerivedComponent>
        DerivedComponent& getComponent(entity_t entity);

        template<class Component>
        int getComponentHandle();

        template<class DerivedComponent>
        std::vector<DerivedComponent>& getComponentList();
        // End of forward declarations

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

        /**
         * Checks whether an entity has a specified tag.
         * @param  entity The entity to check for.
         * @param  tag    The tag, as a string, to check.
         * @return        A boolean indicating whether the entity has that tag.
         */
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

        /**
         * Updates the world so that deleted entities can be cleaned up.
         */
        void refresh();

        /**
         * Adds a specified component to the given entity.
         *
         * @tparam DerivedComponent The type of the component to add.
         * @param  entity           The entity to add the component to.
         */
        template<class DerivedComponent>
        DerivedComponent& addComponent(entity_t entity, auto... args) {
            // TODO: Allow for the component to be initialized with variadic
            // parameters
            detail::staticAssertBase<DerivedComponent>();
            detail::assertEntity(entity);

            detail::assertExclusive(entity, getComponentHandle<DerivedComponent>());

            if(entityHasComponent<DerivedComponent>(entity)) {
                return getComponent<DerivedComponent>(entity);
            }

            // We ask the manager to add the component...
            int index = DerivedComponent::manager.addComponent(entity, args...);
            // Then we store the index of the component within its pool
            // in a map.
            int cHandle = getComponentHandle<DerivedComponent>();
            detail::entityData[entity - 1].indices[cHandle] = index;
            // Modify the mask to reflect that the entity has the component.
            detail::entityData[entity - 1].mask |= cHandle;

            // We check whether we have an instance of the component added
            // to our map; otherwise, we create one.
            try {
                detail::componentInstances.at(cHandle);
            } catch (const std::out_of_range& error) {
                detail::componentInstances[cHandle] = std::make_unique<DerivedComponent>(ENTITY_INVALID);
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
            detail::staticAssertBase<DerivedComponent>();
            detail::assertEntity(entity);
            assert(entityHasComponent<DerivedComponent>(entity));

            int handle = getComponentHandle<DerivedComponent>();
            int index = detail::entityData[entity - 1].indices[handle];
            entity_t entityToUpdate = DerivedComponent::manager.removeComponent(index);

            detail::entityData[entity - 1].mask &= ~handle;


            if(entityToUpdate != ENTITY_INVALID) {
                detail::entityData[entityToUpdate - 1].indices[handle] = index;
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

        /**
         * Disables a component, indicating that it should not interact with
         * the world.
         * @tparam DerivedComponent The component type to disable.
         * @param entity The entity to disable the component for.
         */
        template<class DerivedComponent>
        void disableComponent(entity_t entity) {
            detail::staticAssertBase<DerivedComponent>();
            detail::assertEntity(entity);
            assert(entityHasComponent<DerivedComponent>(entity));

            int handle = getComponentHandle<DerivedComponent>();
            int index = detail::entityData[entity - 1].indices[handle];
            DerivedComponent::manager.setComponentEnabled(index, false);
        }

        /**
         * Enables a component, allowing it to interact with the world.
         * @tparam DerivedComponent The component type to enable.
         * @param entity The entity to enable the component for.
         */
        template<class DerivedComponent>
        void enableComponent(entity_t entity) {
            detail::staticAssertBase<DerivedComponent>();
            detail::assertEntity(entity);
            assert(entityHasComponent<DerivedComponent>(entity));

            int handle = getComponentHandle<DerivedComponent>();
            int index = detail::entityData[entity - 1].indices[handle];
            DerivedComponent::manager.setComponentEnabled(index, true);
        }

        /**
         * Retrieve a component for a specified entity.
         * @tparam DerivedComponent The type of component to retrieve.
         * @param  entity           The entity to retrieve the component for.
         * @return                  A reference to the component.
         */
        template<class DerivedComponent>
        DerivedComponent& getComponent(entity_t entity) {
            detail::staticAssertBase<DerivedComponent>();
            detail::assertEntity(entity);
            assert(entityHasComponent<DerivedComponent>(entity));

            // Firstly get the mask for the component
            int mask = getComponentHandle<DerivedComponent>();
            // Retrieve the component's location within its pool using
            // our mappings
            int index = detail::entityData[entity - 1].indices[mask];
            return DerivedComponent::manager.getComponentList()[index];
        }

        /**
         * A function to check whether an entity has a component attached.
         * @param  entity The handle of the entity to check.
         * @return        A boolean value indicating whether the entity holds the component.
         */
        template<class DerivedComponent>
        constexpr bool entityHasComponent(entity_t entity) {
            detail::staticAssertBase<DerivedComponent>();
            detail::assertEntity(entity);

            int cMask = getComponentHandle<DerivedComponent>();
            if((detail::entityData[entity - 1].mask&cMask) == cMask) {
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
            // TODO: Using typeid seems super inefficient
            //int& handle = detail::componentTypeMap[typeid(Component)];

            /*
             * If the handle is not 0 (component handles cannot be 0),
             * it can be returned. The expression will evaluate to true
             * if the handle exists.
             */
            if(Component::handle) return Component::handle;

            /*
             * Otherwise, we construct a new handle
             * Because we are using a reference, this will also modify
             * the hashed value in the map.
             */
            Component::handle = detail::currentBitsize;

            /*
             * Shift it left by 1 so we can get a unique series of bits for
             * each component
             */
            detail::currentBitsize = detail::currentBitsize << 1;

            return Component::handle;
        }

        /**
         * Gets a list of components for a component type.
         * @tparam  DerivedComponent  The component to get the list for.
         * @return                    A reference to the list.
         */
        template<class DerivedComponent>
        std::vector<DerivedComponent>& getComponentList() {
            detail::staticAssertBase<DerivedComponent>();

            // Basically a convenience wrapper
            return DerivedComponent::manager.getComponentList();
        }

        /**
         * Allows a number of components to be added by default to any
         * entity.
         *
         * @tparam Components The component types to be added.
         */
        template<class ...Components>
        void setDefaultComponents() {
            detail::initiationFuncs.push_back([](entity_t entity) {
                addComponents<Components...>(entity);
            });
        }

        /**
         * Registers a new blueprint with the world. Blueprints can be used
         * to quickly create entities which all have a common set of components.
         * @return The integer handle for the blueprint.
         */
        template<class ...Components>
        int addBlueprint() {
            // A blueprint is just a lambda which adds the components.
            detail::blueprints.push_back([](entity_t entity){
                addComponents<Components...>(entity);
            });

            // The handle is the blueprint's index
            return detail::blueprints.size() - 1;
        }

        /**
         * Configures two components to be exclusive to each other, meaning
         * that if either one is attached to an entity then the other cannot
         * subsequently be attached to the entity.
         * @tparam FirstComponent The first component in the pair.
         * @tparam SecondComponent The second component in the pair.
         */
        template<class FirstComponent, class SecondComponent>
        void setExclusiveComponents() {
            detail::staticAssertBase<FirstComponent>();
            detail::staticAssertBase<SecondComponent>();

            int firstHandle = getComponentHandle<FirstComponent>();
            int secondHandle = getComponentHandle<SecondComponent>();
            // Don't need to check if it already exists in the set
            // because elements in a set are unique so the insertion fails
            detail::exclusiveComponents[firstHandle].insert(secondHandle);
            detail::exclusiveComponents[secondHandle].insert(firstHandle);
        }
    };
}

#endif // WORLD_H
