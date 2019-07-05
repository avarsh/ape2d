#ifndef APE_COMPONENT_DETAIL_H
#define APE_COMPONENT_DETAIL_H

#include <ape/core/constants.h>

namespace ape {
    namespace detail {
        /*
         * A base class for components. Custom components should not derive from
         * this class! This is meant to be used to group components in
         * certain collections internally within the engine.
         */
        class BaseComponent {
        public:
            /*
             * A virtual function enabling component removal within
             * the world.
             */
            virtual entity_t detach(int index) = 0;
        };
    }
}

#endif