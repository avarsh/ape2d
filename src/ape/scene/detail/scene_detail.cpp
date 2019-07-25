#include <ape/scene/detail/scene_detail.h>
#include <ape/scene/camera.h>
#include <ape/core/world.h>
#include <ape/scene/node.h>
#include <ape/core/transform.h>
#include <ape/graphics/window.h>
#include <ape/graphics/sprite.h>

namespace ape {
    namespace scene {
        namespace detail {
            void init() {
                ROOT_NODE = world::createEntity();
                world::addComponent<Node>(ROOT_NODE);

                DEFAULT_CAMERA = world::createEntity();
                world::addComponent<Camera>(DEFAULT_CAMERA);
                world::addComponent<Transform>(DEFAULT_CAMERA);

                world::entityDeleted.addCallback([](entity_t entity) {
                    if (world::entityHasComponent<Node>(entity)) {
                        auto& node = world::getComponent<Node>(entity);
                        node.detach();
                        for (const entity_t child : node.getChildren()) {
                            world::deleteEntity(child);
                        }
                    }
                });
            }

            void render() {
                traverse(ROOT_NODE);
            }

            void traverse(const entity_t entity) {
                /* TODO: Since trees can become large, use non-recursive traversal. */
                auto& node = world::getComponent<Node>(entity);

                // Apply local transformations
                auto& local = world::getComponent<Transform>(entity);
                auto& parent = world::getComponent<Node>(node.getParent()).getGlobalTransform();
                auto& global = node.getGlobalTransform(); 
                // Update the global transformation of the node
                global.position = parent.position + local.position;
                global.velocity = parent.velocity + local.velocity;
                global.rotation = parent.rotation + local.rotation;
                global.scale    = parent.scale + local.scale;

                // Render this 
                if (world::entityHasComponent<Sprite>(entity)) {
                    // Set sprite position, viewport, camera etc here
                    window::draw(world::getComponent<Sprite>(entity), global);
                } /* TODO: Primitives */

                // Traverse children
                for (const entity_t child : node.getChildren()) {
                    traverse(child);
                }
            }
        }
    }
}