#ifndef NODE_H
#define NODE_H

#include <ape/core/component.h>
#include <ape/core/world.h>
#include <list>

namespace ape {

    struct NodeTypes {
        static int ABSTRACT;
        static int ACTUALIZED;
    };

    class Node : public Component<Node> {
    public:
        void setParent(World& world, entity_t parent);
        void setIndex(World& world, int index);
        int getIndex();
        entity_t getParent();
        std::list<entity_t>& getChildren();

        int traversingChild {-1};
        int nodeType {NodeTypes::ACTUALIZED};
    private:
        // We're using lists here because the nodes may be moving
        // around within the scene quite a lot - for example, when
        // moving layers around, destroying items etc.
        // Lists have constant time insertion and deletion
        std::list<entity_t> children;
        entity_t parent {ENTITY_INVALID};
        int index;
    };

}

#endif // NODE_H
