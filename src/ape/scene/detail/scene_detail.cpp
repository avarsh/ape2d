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
                Transform transform(ENTITY_INVALID);
                traverse(ROOT_NODE, transform);
            }

            void traverse(const entity_t entity, Transform transform) {
                const auto& node = world::getComponent<Node>(entity);

                // Apply local transformations
                auto& local = world::getComponent<Transform>(entity);
                transform.position += local.position;
                transform.velocity += local.velocity;
                transform.rotation += local.rotation;
                transform.scale    += local.scale;

                // Render this 
                if (world::entityHasComponent<Sprite>(entity)) {
                    // Set sprite position, viewport, camera etc here
                    window::draw(world::getComponent<Sprite>(entity), transform);
                } /* TODO: Primitives */

                // Traverse children
                for (const entity_t child : node.getChildren()) {
                    traverse(child, transform);
                }
            }
        }
    }
}