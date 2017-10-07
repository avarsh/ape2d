#include <ape/ape.h>

int main() {
    ape::Engine engine;
    ape::Graphics& graphics = engine.graphics;
    ape::World& world = engine.world;

    graphics.window.create(800, 600, "Tilesheet example");

    auto tilesheet = graphics.textureStore.loadTexture("examples/images/tilesheet.png");
    if(tilesheet == -1) {
        return 1;
    }

    for(int i = 0; i < 2; i++) {
        auto entity = world.createEntity();
        auto& transform = world.addComponent<ape::Transform>(entity);
        auto& sprite = world.addComponent<ape::Sprite>(entity);
        auto& node = world.addComponent<ape::Node>(entity);

        transform.setPosition(64 * i, 64 * i);
        sprite.setTextureID(tilesheet, graphics.textureStore);
        sprite.setSubRect(0, i * 64, 64, 64);
        node.setParent(world, ape::Scene::rootNode);
    }

    while(graphics.window.isOpen()) {
        glfwPollEvents();

        graphics.window.clear(ape::Colors::Sky);
        engine.render();
        graphics.window.display();
    }
}
