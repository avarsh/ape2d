#ifndef COMPONENT_H
#define COMPONENT_H

#include <ape/core/defines.h>
#include <ape/core/componentmanager.h>
#include <ape/core/detail/component_detail.h>

namespace ape {

    /**
     * A derived component class, intended to be inherited by all other
     * component implementations. The remove function
     */

    template<class DerivedComponent>
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
        // be stored in a vector, as it is templated). Since the base component
        // does not have a component manager, it instead implements a virtual
        // function to remove the component. Since we're storing pointers,
        // when we call the remove on the base component, we actually call this
        // version (polymorphism!) of the function.
        //
        // The manager removes a component by swapping the component with
        // the last one in the pool. It then deletes the last component.
        // Since entities have maps to each component's index, the function
        // returns the parent entity of the swapped component, so the world
        // can update it.
        //
        // Suggestions for less messy solutions are appreciated.

        virtual int remove(int index) {
            // Ask the manager to remove it...
            return manager.removeComponent(index);
        }

        // The parent entity
        entity_t entity { ENTITY_INVALID };
        // Whether the component is enabled or not
        bool enabled {true};

        // The manager for the component, shared by all instances of the
        // component.
        static ComponentManager<DerivedComponent> manager;
        static int handle;
    };

    template<class DerivedComponent>
    ComponentManager<DerivedComponent> Component<DerivedComponent>::manager;

    template<class DerivedComponent>
    int Component<DerivedComponent>::handle = 0;
}

#endif
