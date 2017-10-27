#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <vector>   /* std::vector */
#include <cassert>  /* assert()    */

#include <ape/core/defines.h>

namespace ape {

    /**
     * The component manager manages each component, including
     * deletion and insertion of new components. Functions should not
     * be invoked manually; the functions in the world namespace
     * should be used instead.
     * @tparam The component to manage.
     */

    template<class DerivedComponent>
    class ComponentManager {
    public:
        /**
         * Adds a component to the list.
         * @param  entity The entity the component is attached to.
         * @return        The index of the component in the list.
         */
        int addComponent(entity_t entity, auto... args) {
            DerivedComponent component(entity, args...);
            componentList.push_back(component);
            return componentList.size() - 1;
        }

        /**
         * Removes a component from the list.
         * @param  index The component's index within it's pool.
         * @return       The entity holding the component which has been moved.
         */
        entity_t removeComponent(int index) {
            _assertComponent(index);
            if(index != (componentList.size() - 1)) {
                std::swap(componentList[index], componentList.back());
                componentList.pop_back();

                return componentList[index].getEntity();
            }

            componentList.pop_back();
            return 0;
        }

        void setComponentEnabled(int index, bool isEnabled) {
            _assertComponent(index);
            componentList[index].enabled = isEnabled;
        }

        /**
         * Gets the list of components.
         * @return A reference to the vector of component instances.
         */
        std::vector<DerivedComponent>& getComponentList() {
            return componentList;
        }

    private:
        std::vector<DerivedComponent> componentList;

        void _assertComponent(int index) {
            assert(index >= 0);
            assert(index < componentList.size());
        }
    };
}

#endif
