#include <ape/scene/node.h>
#include <iterator>
#include <algorithm>

namespace ape {

    void Node::setParent(entity_t parent) {
        if(world::entityHasComponent<Node>(parent)) {
            this->parent = parent;
            auto& parentNode = world::getComponent<Node>(parent);
            // Class instances are allowed to access private data
            // from any other class instance...
            parentNode.children.push_back(this->entity);
            index = parentNode.children.size() - 1;

            if(parent != scene::rootNode) {
                this->cameraEntity = parentNode.cameraEntity;
                this->rootParent = parentNode.rootParent;
            } else {
                cameraEntity = scene::defaultCamera;
                this->rootParent = this->entity;
            }
        } else {
            // Warning or exception here
        }
    }

    void Node::setIndex(int index) {
        if(this->index == index) {
            return;
        }

        auto& parentNode = world::getComponent<Node>(parent);
        int oldIndex = this->index;
        this->index = index;

        auto iter = parentNode.children.begin();
        // Lists have bidirectional iterators so we can only
        // increment them.
        std::advance(iter, oldIndex);

        int lastIndex = parentNode.children.size() - 1;
        if(index > lastIndex) {
            // The index is out of bounds but not to worry!
            // Perhaps the user wanted to do thiNodes on purpose
            // We shall simply create invalid entities and fill the list with
            // them; then, when the user adds any other node to the parent,
            // if the index is occupied by an invalid entity, then we can
            // replace it with the appropriate node
            for(int i = 0; i < (index - lastIndex); i++) {
                parentNode.children.push_back(ENTITY_INVALID);
            }

            // Now we can erase the node at the old index
            parentNode.children.erase(iter);
            // and add it to the end
            parentNode.children.push_back(this->entity);
        } else {
            parentNode.children.erase(iter);
            auto newIter = parentNode.children.begin();
            std::advance(newIter, index);
            parentNode.children.insert(newIter, this->entity);
        }

        // If the node is shifted to a lower index, then we need to add one to
        // the index of all nodes from (index + 1) -> oldIndex (since
        // index < oldIndex) If the node is shifted to a higher index, then we
        // need to subtract one from the index of all nodes from
        // oldIndex -> (index - 1) (since index > oldIndex).

        auto childIter = parentNode.children.begin();

        int start = index < oldIndex ? index + 1 : oldIndex;
        int end = index < oldIndex ? oldIndex : index - 1;
        auto move = [index, oldIndex](auto val) {
            if(index < oldIndex) val++;
            else val--;
        };

        std::advance(childIter, start);
        for(int i = start; i <= end; i++) {
            if(*childIter != ENTITY_INVALID) {
                move(world::getComponent<Node>(*childIter).index);
            }
            move(childIter);
        }
    }

    int Node::getIndex() {
        return index;
    }

    entity_t Node::getParent() {
        return parent;
    }

    std::list<entity_t>& Node::getChildren() {
        return children;
    }

    void Node::setCamera(entity_t camera) {
        // TODO: log some kind of error here
        if(parent == ENTITY_INVALID) {
            return;
        }

        if(parent != scene::rootNode) {
            return;
        }

        cameraEntity = camera;
        // Recursively set camera for all children
        for(auto& node : world::getComponentList<Node>()) {
            if(node.rootParent == this->entity) {
                node.cameraEntity = camera;
            }
        }

    }

    entity_t Node::getCamera() {
        return cameraEntity;
    }
}
