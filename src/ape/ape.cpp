#include <ape/ape.h>

namespace ape {

    Engine::Engine() : graphics(world) { }

    Graphics& Engine::getGraphics() {
        return graphics;
    }

    World& Engine::getWorld() {
        return world;
    }

    void Engine::pollEvents() {
        glfwPollEvents();
    }
}
