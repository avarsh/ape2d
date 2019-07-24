#ifndef APE_NODE_H
#define APE_NODE_H

#include <ape/core/component.h>
#include <list>

namespace ape {
    /**
     * Represents a type of node, either OBJECT or TRANSFORM.
     * A TRANSFORM node applies a transformation to all children.
     */
    enum class NodeType {
        OBJECT,
        TRANSFORM
    };

    /**
     * Node component for use in the scene graph. Holds the parent,
     * a camera to be associated with, children and the type of node. 
     */
    struct Node : public Component<Node> {
        Node(entity_t entity) : Component<Node>(entity) {}

        entity_t parent;
        entity_t cameraEnity;
        std::list<entity_t> children;
        NodeType nodeType { NodeType::OBJECT };

    };
}

#endif 