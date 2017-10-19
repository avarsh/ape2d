#include <ape/ape.h>

namespace ape {
    void init() {
        graphics::init();
        scene::init();
        ape::window::createdEvent.addCallback([&](Vec2i size){
            input::init();
        });
    }

    void update() {
        glfwPollEvents();
        graphics::begin();
        scene::render();
        graphics::end();
    }
}
