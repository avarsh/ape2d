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
        const entity_t getParent() const;

        /**
         * Retrieves the associated camera for this entity.
         * @return The camera entity.
         */
        const entity_t getCamera() const;

        /**
         * Sets a camera entity to be associated with this node.
         */
        void setCamera(entity_t camera);

        /**
         * Retrieves a read-only reference to the children.
         */
        const std::list<entity_t>& getChildren() const;

        /**
         * Retrieves the global transformation of the node.
         */
        Transform& getGlobalTransform();

        /**
         * Sets the node to be positioned relative to the window
         * instead of its parent. Useful for UI elements.
         * @param setting Whether the node is positioned relative to the window.
         */
        void setRelativeToWindow(bool setting);

        /**
         * Retrieves whether the node is positioned relative to the window.
         * @return Whether the node is relative to the window.
         */
        bool getRelativeToWindow();
    private:
        entity_t parent {ENTITY_INVALID};
        /* TODO: If no camera is set, use the default camera */
        entity_t camera {ENTITY_INVALID};
        std::list<entity_t> children;

        void propogateCamera(entity_t camera);
        Transform globalTransform;
        bool relativeToWindow;
    };

    namespace scene {
        extern entity_t ROOT_NODE;
    }
}

#endif 