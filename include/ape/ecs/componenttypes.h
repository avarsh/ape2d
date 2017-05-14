#ifndef COMPONENT_TYPES_H
#define COMPONENT_TYPES_H

#include <unordered_map> /* std::unordered_map */
#include <typeinfo>      /* typeid             */
#include <typeindex>     /* std::type_index    */
#include <stdexcept>     /* std::out_of_range  */

namespace ape {

    /**
     * A class which manages the types for each component.
     */
    class ComponentTypeManager {
        // Unordered maps are faster than maps!
        using ImplComponentTypeMap = std::unordered_map<std::type_index, int>;

        public:
            /**
             * Function to get the type information about a component.
             * @tparam The component class to get information about.
             * @return The unique integer handle for the component's type.
             */
            template<class Component>
            int getComponentHandle() {
                // This is way faster than using a find and then inserting into map
                int handle = 0;
                try {
                    handle = mComponentTypeMap.at(typeid(Component));
                } catch(const std::out_of_range& error) {
                    // The type does not yet exist in our map, so we make a new
                    // component handle to associate with the type
                    handle = mComponentTypeMap[typeid(Component)] = currentBitsize;
                    currentBitsize = currentBitsize << 1;
                }

                return handle;
            }

            int getCurrentBitsize() {
                return currentBitsize;
            }

        private:
            ImplComponentTypeMap mComponentTypeMap;
            int currentBitsize {1}; // Maybe use std::bitset in future?
    };
}

#endif //COMPONENT_TYPES_H
