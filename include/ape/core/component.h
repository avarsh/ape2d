#ifndef COMPONENT_H
#define COMPONENT_H

#include <ape/core/defines.h>
#include <ape/core/componentmanager.h>
#include <ape/core/detail/component_detail.h>

namespace ape {

    // Forward declarations for friend functions of the component class.
    // Now that the world class is abolished in favour of a namespace,
    // we cannot friend the entire class as it were.
    namespace world {
        template<class DerivedComponent>
        DerivedComponent& addComponent(entity_t entity, auto... args);

        template<class DerivedComponent>
        void removeComponent(entity_t entity);

        template<class DerivedComponent>
        void disableComponent(entity_t entity);

        template<class DerivedComponent>
        void enableComponent(entity_t entity);

        template<class DerivedComponent>
        DerivedComponent& getComponent(entity_t entity);

        template<class DerivedComponent>
        std::vector<DerivedComponent>& getComponentList();
    }

    /**
     * A derived component class, intended to be inherited by all other
     * component implementations. The remove function
     */

    template<class Derived>
    struct Component : public detail::BaseComponent {

        /**
         * Implementation of the remove function, enabling a component
         * to be removed from its pool. Not intended to be used outside
         * of the API. Calls the manager's remove function.
         * @param  index The component's index within it's pool.
         * @return       The entity holding the component which has been moved.
         */

        // Side note : this is needed because the world class effectively
        // stores an instance of each component type that exists, by creating
        // a vector of pointers to the base component (since this class cannot
        // be stored in a vector, as it is templated). Since template<class DerivedComponent>
        // does not have a component manager, it instead implements a virtual
        // function to remove the component. Since we're storing pointers,
        // when we call the remove on the base component, we actually call this
        // version (polymorphism!) of the function.
        //DerivedComponent
        // The manager removes a component by swapping the component with
        // the last one in the pool. It then deletes the last component.
        // Since entities have maps to each component's index, the function
        // returns the parent entity of the swapped component, so the world
        // can update it.
        //
        // Suggestions for less messy solutions are appreciated.

        Component(entity_t entity) : entity(entity) {

        }

        virtual int remove(int index) {
            // Ask the manager to remove it...
            return manager.removeComponent(index);
        }

        entity_t getEntity() {
            return entity;static int handle;
        }

        static int handle;

    protected:
        // The parent entity
        entity_t entity { ENTITY_INVALID };

        // Whether the component is enabled or not
        bool enabled {true};

        // The manager for the component, shared by all instances of the
        // component.
        static ComponentManager<Derived> manager;

        // Now we friend some functions in the world namespace which
        // need to invoke the component manager
        template<class DerivedComponent>
        friend DerivedComponent& world::addComponent(entity_t entity, auto... args);

        template<class DerivedComponent>
        friend void world::removeComponent(entity_t entity);

        template<class DerivedComponent>
        friend void world::disableComponent(entity_t entity);

        template<class DerivedComponent>
        friend void world::enableComponent(entity_t entity);

        template<class DerivedComponent>
        friend DerivedComponent& world::getComponent(entity_t entity);

        template<class DerivedComponent>
        friend std::vector<DerivedComponent>& world::getComponentList();
    };

    template<class Derived>
    ComponentManager<Derived> Component<Derived>::manager;

    template<class Derived>
    int Component<Derived>::handle = 0;
}

#endif
