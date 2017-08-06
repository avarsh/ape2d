#include <ape/core/scene.h>

namespace ape {
    entity_t Scene::rootNode = ENTITY_INVALID;

    Scene::Scene(World& world) : world(world) {

    }

    void Scene::init() {
        rootNode = world.createEntity();
        auto& node = world.addComponent<Node>(rootNode);
    }

    void Scene::traverse(Graphics& graphics) {
        /*
         * To traverse the tree:
         *  1. for any node, get the first child and draw it
         *  2. do this recursively until the node has no MORE children
         *      - Check this by adding one to the current index, then
         *        seeing if its equal to size, in which case, reset to -1
         *        and return
         *  3. then go back up one level and go to the next child
         *  4. do 1, 2 and 3 recursively
         *  5. if there are no more children, go back up a level and it again 
         *  6. repeat until back at root node AND no more children left to visit
         */

        _traverse(rootNode, graphics);
    }

    void Scene::_traverse(entity_t entity, Graphics& graphics) {
        auto& node = world.getComponent<Node>(entity);

        if(node.traversingChild == -1) {
            // This is the first time we have visited this node, so render it
            // if possible
            if(world.entityHasComponent<Sprite>(entity)) {
                graphics.draw(&world.getComponent<Sprite>(entity));
            }
        }

        // Traverse the next child
        // Since this is set to -1 initially, increasing it will
        // point to the first child at index 0
        node.traversingChild++;

        if(node.traversingChild == node.getChildren().size()) {
            node.traversingChild = -1; // Reset the index

            // If the parent is not invalid, then traverse it
            // and point to the next child
            if(node.getParent() != ENTITY_INVALID) {
                return _traverse(node.getParent(), graphics);
            } else {
                // If the parent is invalid then we are back at the root node,
                // so just end the recursion
                return;
            }
        } else {
            // Otherwise, traverse the child
            auto iter = node.getChildren().begin();
            std::advance(iter, node.traversingChild);
            _traverse(*iter, graphics);
        }
    }
}
