#include <ape/ape.h>

namespace ape {
    void init() {
        graphics::init();
        scene::init();
    }

    void update() {
        glfwPollEvents();
        scene::render();
    }
}
