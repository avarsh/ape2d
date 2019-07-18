#ifndef APE_NODE_H
#define APE_NODE_H

#include <ape/core/component.h>
#include <list>

namespace ape {
    enum class NodeType {
        OBJECT,
        TRANSFORM
    };

    struct Node : public Component<Node> {
        Node(entity_t entity) : Component<Node>(entity) {}

        entity_t parent;
        entity_t cameraEnity;
        std::list<entity_t> children;
        NodeType nodeType { NodeType::OBJECT };

    };
}

#endif 