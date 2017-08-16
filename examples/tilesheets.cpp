#include <ape/ape.h>

int main() {
    ape::Engine engine;
    auto& window = engine.getGraphics().getWindow();
    auto& textureStore = engine.getGraphics().getTextureStore();
    auto& world = engine.getWorld();

    window.create(800, 600, "Tilesheet example");

    auto tilesheet = textureStore.loadTexture("examples/images/tilesheet.png");
    if(tilesheet == -1) {
        return 1;
    }

    for(int i = 0; i < 2; i++) {
        auto entity = world.createEntity();
        auto& transform = world.addComponent<ape::Transform>(entity);
        auto& sprite = world.addComponent<ape::Sprite>(entity);
        auto& node = world.addComponent<ape::Node>(entity);

        transform.setPosition(64 * i, 64 * i);
        sprite.setTextureID(tilesheet, textureStore);
        sprite.setSubRect(0, i * 64, 64, 64);
        node.setParent(world, ape::Scene::rootNode);
    }

    while(window.isOpen()) {
        glfwPollEvents();

        window.clear(ape::Colors::Sky);
        engine.render();
        window.display();
    }
}
