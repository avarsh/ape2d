#include <ape/scene/detail/scene_detail.h>

namespace ape {
    namespace scene {
        namespace detail {
            void traverse(entity_t entity) {

                auto& node = world::getComponent<Node>(entity);

                if(node.traversingChild == -1) {
                    // This is the first time we have visited this node, so render it
                    // if possible
                    if(world::entityHasComponent<Sprite>(entity)) {
                        graphics::draw(&world::getComponent<Sprite>(entity));
                    }
                }

                // Traverse the next child
                // Since this is set to -1 initially, increasing it will
                // point to the first child at index 0
                node.traversingChild++;
                bool endPoint = false;

                if(node.traversingChild == node.getChildren().size()) {
                    endPoint = true;
                } else {
                    // Otherwise, traverse the child
                    auto iter = node.getChildren().begin();
                    std::advance(iter, node.traversingChild);
                    while(*iter == ENTITY_INVALID) {
                        iter++;
                        node.traversingChild++;
                        if(iter == node.getChildren().end()) {
                            endPoint = true;
                        }
                    }
                    traverse(*iter);
                }

                if(endPoint) {
                    node.traversingChild = -1; // Reset the index

                    // If the parent is not invalid, then traverse it
                    // and point to the next child
                    if(node.getParent() != ENTITY_INVALID) {
                        return traverse(node.getParent());
                    } else {
                        // If the parent is invalid then we are back at the root node,
                        // so just end the recursion
                        return;
                    }
                }
            }
        }
    }
}
