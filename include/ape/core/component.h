#ifndef APE_COMPONENT_H
#define APE_COMPONENT_H

#include <ape/core/constants.h>
#include <ape/core/detail/component_detail.h>

namespace ape {

    template<class Derived>
    class Component : public detail::BaseComponent {
    public:
        Component(entity_t entity) : entity(entity) { }

        /**
         * Retrieves the entity which holds the component.
         */
        entity_t getEntity() {
            return entity;
        }

        /**
         * Returns the pool of all components of this type.
         */

        /* TODO: friend the world namespace? */
        static std::vector<Derived>& getPool() {
            return pool;
        }

        /**
         * Enables the component, allowing it to be interacted with.
         */
        void enable() {
            enabled = true;
        }

        /**
         * Disables the component, stopping it from being interacted with.
         */
        void disable() {
            enabled = false;
        }

        entity_t detach(int index) {
            if (index != (pool.size() - 1)) {
                std::swap(pool[index], pool.back());
                pool.pop_back();
                return pool[index].getEntity();
            }

            pool.pop_back();
            return ENTITY_INVALID;
        }

        static int handle;
    protected:
        static std::vector<Derived> pool;

        entity_t entity {ENTITY_INVALID};
        bool enabled {true};

    };

    template<class Derived>
    std::vector<Derived> Component<Derived>::pool;

    template<class Derived>
    int Component<Derived>::handle = 0;
}

#endif