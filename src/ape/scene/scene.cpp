#include <ape/scene/scene.h>

namespace ape {
    namespace scene {
        entity_t rootNode = ENTITY_INVALID;

        void init() {
            rootNode = world::createEntity();
            world::addComponent<Node>(rootNode);

            defaultCamera = world::createEntity();
            auto& camera = world::addComponent<Camera>(defaultCamera);
        }

        void render() {
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

            detail::traverse(rootNode);
        }
    }
}
