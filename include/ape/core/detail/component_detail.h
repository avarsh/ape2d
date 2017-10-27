#ifndef COMPONENT_DETAIL_H
#define COMPONENT_DETAIL_H

#include <ape/core/defines.h>

namespace ape {
    namespace detail {

        /*
         * A base class for components. Custom components should not derive from
         * this class! This is meant to be used to group components in
         * certain collections internally within the engine.
         */
        struct BaseComponent {
            /*
             * A virtual function enabling component removal within
             * the world.
             */
            virtual int remove(int index) = 0;
        };
    }
}

#endif // COMPONENT_DETAIL_H
