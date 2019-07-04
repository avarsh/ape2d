#ifndef APE_WORLD_H
#define APE_WORLD_H

#include <ape/core/constants.h>
#include <ape/core/detail/world_detail.h>

namespace ape {

    /**
     * @brief The world provides functions to manage the ECS within APE.
     * 
     * The world manages the creation and the lifetime of entities and
     * allows information about entities such as components to be retrieved.
     */ 
    namespace world {

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
         * Get the next alive entity in the world after a given entity.
         * @param  current       The entity to start from.
         * @return               The handle of the next alive entity.
         */
        entity_t getNext(entity_t current);

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

            if(entityHasComponent<DerivedComponent>(entity)) {
                return getComponent<DerivedComponent>(entity);
            }
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
            detail::assertEntity(entity, "world::entityHasComponent");

            int cMask = getComponentHandle<DerivedComponent>();
            if((detail::entityData[entity - 1].mask & cMask) == cMask) {
                return true;
            }

            return false;
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
    }
}

#endif // APE_WORLD_H