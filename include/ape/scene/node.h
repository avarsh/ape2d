#ifndef NODE_H
#define NODE_H

#include <ape/core/component.h>
#include <ape/core/world.h>
#include <ape/scene/camera.h>
#include <list>

namespace ape {

    // Forward declaration
    namespace scene {
        extern entity_t rootNode;
    }

    class Node : public Component<Node> {
    public:
        Node(entity_t entity) : Component<Node>(entity) {}

        Node(entity_t entity, entity_t parent) : Component<Node>(entity) {
            setParent(parent);
        }

        void setParent(entity_t parent);
        void setIndex(int index);
        int getIndex();
        void detachFromParent();
        entity_t getParent();
        std::list<entity_t>& getChildren();

        void setCamera(entity_t camera);
        entity_t getCamera();

        int traversingChild {-1};
    private:
        // We're using lists here because the nodes may be moving
        // around within the scene quite a lot - for example, when
        // moving layers around, destroying items etc.
        // Lists have constant time insertion and deletion
        std::list<entity_t> children;
        entity_t parent {ENTITY_INVALID};
        entity_t cameraEntity {ENTITY_INVALID};
        entity_t rootParent {ENTITY_INVALID};
        int index;
    };

}

#endif // NODE_H
