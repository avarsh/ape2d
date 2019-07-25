#ifndef APE_NODE_H
#define APE_NODE_H

#include <ape/core/component.h>
#include <ape/core/transform.h>
#include <list>

namespace ape {
    /**
     * Node component for use in the scene graph. Holds the parent,
     * a camera to be associated with, children and the type of node. 
     */
    struct Node : public Component<Node> {
        Node(entity_t entity);

        /**
         * Add an entity as a child of the entity which holds this node.
         * @param child The entity to add as a child.
         */
        void addChild(entity_t child);

        /**
         * Detaches this entity from its parent.
         */
        void detach();

        /**
         * Retrieves the parent entity.
         * @return The parent entity.
         */
        entity_t getParent();

        /**
         * Retrieves the associated camera for this entity.
         * @return The camera entity.
         */
        entity_t getCamera();

        /**
         * Sets a camera entity to be associated with this node.
         */
        void setCamera(entity_t camera);

        /**
         * Retrieves a read-only reference to the children.
         */
        const std::list<entity_t>& getChildren() const;

        
    private:
        entity_t parent;
        /* TODO: If no camera is set, use the default camera */
        entity_t camera {ENTITY_INVALID};
        std::list<entity_t> children;

        void propogateCamera(entity_t camera);
    };

    namespace scene {
        extern entity_t ROOT_NODE;
    }
}

#endif 