#include <ape/ape.h>

namespace ape {
    void init() {
        graphics::init();
        scene::init();
    }

    void update() {
        glfwPollEvents();
        graphics::begin();
        scene::render();
        graphics::end();
    }
}
