#include <ape/scene/node.h>
#include <ape/core/world.h>
#include <ape/core/debug.h>

namespace ape {
    namespace scene {
        entity_t ROOT_NODE = ENTITY_INVALID;
    }

    Node::Node(entity_t entity) : Component<Node>(entity), 
        globalTransform(ENTITY_INVALID) { }

    void Node::addChild(entity_t child) {
        children.push_back(child);
        auto& childNode = world::getComponent<Node>(child);
        childNode.parent = entity;
        childNode.propogateCamera(this->camera);
    }

    void Node::detach() {
        auto& parentNode = world::getComponent<Node>(parent);
        parentNode.children.remove(entity);
        camera = ENTITY_INVALID;
    }

    const entity_t Node::getParent() const {
        return parent;
    }

    const entity_t Node::getCamera() const {
        return camera;
    }

    void Node::setCamera(entity_t camera) {
        ASSERT_MSG (parent == scene::ROOT_NODE, "Node is not direct child of root.");
        propogateCamera(camera);
        /* TODO: Allow some kind of configuration if the camera is deleted.
           Right now we just set it to invalid, aka default camera.
         */

        /* TODO: Consider some kind of entity storage class which handles
            entity deletion safely. */
        world::entityDeleted.addCallback([camera, this](entity_t entity){
            if (entity == camera) {
                this->setCamera(ENTITY_INVALID);
            }
        });
    }

    void Node::propogateCamera(entity_t camera) {
        this->camera = camera;
        for (const auto& child : children) {
            world::getComponent<Node>(child).propogateCamera(camera);
        }
    }

    const std::list<entity_t>& Node::getChildren() const {
        return this->children;
    };
    
    Transform& Node::getGlobalTransform() {
        return globalTransform;
    }
}