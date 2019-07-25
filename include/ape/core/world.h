#ifndef APE_WORLD_H
#define APE_WORLD_H

#include <ape/core/constants.h>
#include <ape/core/detail/world_detail.h>
#include <ape/core/component.h>
#include <ape/core/event.h>

#include <cassert>

namespace ape {

    /**
     * @brief The world provides functions to manage the ECS within APE.
     * 
     * The world manages the creation and the lifetime of entities and
     * allows information about entities such as components to be retrieved.
     */ 
    namespace world {

        // Forward declarations
        template<class DerivedComponent>
        constexpr bool entityHasComponent(entity_t entity);

        template<class DerivedComponent>
        DerivedComponent& getComponent(entity_t entity);

        template<class Component>
        int getComponentHandle();

        /**
         * @brief Creates a new entity, or reassigns one which has been 
         * previously deleted.
         * 
         * @return The 32 bit integer handle for the entity.
         */
        entity_t createEntity();

        /**
         * Creates a new entity from a predefined blueprint.
         * @param  blueprint The handle for the blueprint which will be used.
         * @return           The handle for the entity.
         */
        entity_t createEntityFromBlueprint(blueprint_t blueprint);

        /**
         * Destroys an entity, deleting all attached components and marking
         * it as dead.
         *
         * @param entity The entity to be destroyed.
         */
        void deleteEntity(entity_t entity);

        /**
         * Get the next alive entity in the world after a given entity.
         * @param  current       The entity to start from.
         * @return               The handle of the next alive entity.
         */
        entity_t getNext(entity_t current);

        /**
         * Get the first alive entity in the world.
         * @return               The handle of the first alive entity.
         */
        entity_t getFirstEntity();

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
        DerivedComponent& addComponent(entity_t entity) {
            /* TODO: Allow component initialisation with variadic parameters */
            detail::staticAssertBase<DerivedComponent>();
            detail::assertEntity(entity, "world::addComponent");

            /* TODO: Add exclusive components if needed */

            if(!entityHasComponent<DerivedComponent>(entity)) {
                // Create component and store it in it's pool
                DerivedComponent component(entity);
                DerivedComponent::getPool().push_back(component);
                int index = DerivedComponent::getPool().size() - 1;

                // Store the index of the component within a map
                int cHandle = getComponentHandle<DerivedComponent>();
                detail::getData(entity).indices[cHandle] = index;
                // Modify the mask to reflect that the entity has the component
                detail::getData(entity).mask |= cHandle;

                // Check whether we have an instance of the component in the map
                // Otherwise create one
                try {
                    detail::componentInstances.at(cHandle);
                } catch (const std::out_of_range& error) {
                    detail::componentInstances[cHandle] = std::make_unique<DerivedComponent>(ENTITY_INVALID);
                }
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
            auto& component = getComponent<DerivedComponent>(entity);

            int mask = getComponentHandle<DerivedComponent>();
            int index = detail::getData(entity).indices[mask];
            
            entity_t toUpdate = component.detach(index);
            if (toUpdate != ENTITY_INVALID) {
                detail::getData(toUpdate).indices[mask] = index;
            }

            detail::getData(entity).mask &= ~mask;
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
         * Retrieve a component for a specified entity.
         * @tparam DerivedComponent The type of component to retrieve.
         * @param  entity           The entity to retrieve the component for.
         * @return                  A reference to the component.
         */
        template<class DerivedComponent>
        DerivedComponent& getComponent(entity_t entity) {
            detail::staticAssertBase<DerivedComponent>();
            detail::assertEntity(entity, "world::getComponent");
            assert(entityHasComponent<DerivedComponent>(entity));

            // Firstly get the mask for the component
            int mask = getComponentHandle<DerivedComponent>();
            // Retrieve the component's location within its pool using
            // our mappings
            int index = detail::getData(entity).indices[mask];
            return DerivedComponent::getPool()[index];
        }   

        /**
         * A function to check whether an entity has a component attached.
         * @param  entity The handle of the entity to check.
         * @return        A boolean value indicating whether the entity holds the component.
         */
        template<class DerivedComponent>
        constexpr bool entityHasComponent(entity_t entity) {
            detail::staticAssertBase<DerivedComponent>();
            detail::assertEntity(entity, "world::entityHasComponent");

            int cMask = getComponentHandle<DerivedComponent>();
            if((detail::getData(entity).mask & cMask) == cMask) {
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
        std::vector<DerivedComponent>& getComponentPool() {
            detail::staticAssertBase<DerivedComponent>();

            return DerivedComponent::getPool();
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
         * @return The handle for the blueprint.
         */
        template<class ...Components>
        blueprint_t addBlueprint() {
            // A blueprint is just a lambda which adds the components.
            detail::blueprints.push_back([](entity_t entity){
                addComponents<Components...>(entity);
            });

            // The handle is the blueprint's index
            return detail::blueprints.size() - 1;
        }

        extern Event<entity_t> entityDeleted;
    }
}

#endif