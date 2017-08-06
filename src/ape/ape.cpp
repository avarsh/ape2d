#include <ape/ape.h>

namespace ape {
    Engine::Engine() : graphics(world), scene(world) {
        scene.init();
    }

    Graphics& Engine::getGraphics() {
        return graphics;
    }

    World& Engine::getWorld() {
        return world;
    }

    void Engine::render() {
        graphics.begin();
        scene.traverse(graphics);
        graphics.end();
    }
}
