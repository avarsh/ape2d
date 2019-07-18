#include <ape/scene/detail/scene_detail.h>
#include <ape/scene/camera.h>
#include <ape/core/world.h>
#include <ape/scene/node.h>
#include <ape/core/transform.h>

namespace ape {
    namespace scene {
        namespace detail {
            entity_t ROOT_NODE = ENTITY_INVALID;

            void init() {
                ROOT_NODE = world::createEntity();
                world::addComponent<Node>(ROOT_NODE);

                DEFAULT_CAMERA = world::createEntity();
                world::addComponent<Camera>(DEFAULT_CAMERA);
                world::addComponent<Transform>(DEFAULT_CAMERA);

                /* TODO: Set the display area on window creation event */

                /* TODO: On entity deletion detach it from the tree */
            }

            void render() {

            }

            void traverse() {
                
            }
        }
    }
}