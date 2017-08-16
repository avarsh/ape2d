#include <ape/ape.h>
#include <ape/core/world.h>

int main() {
    ape::Engine engine;
    auto& window = engine.getGraphics().getWindow();
    auto& textureStore = engine.getGraphics().getTextureStore();
    auto& world = engine.getWorld();

    window.create(800, 600, "Single Sprite Example");

    auto spriteTexture = textureStore.loadTexture("examples/images/mario.png");

    if(spriteTexture == -1) {
        return 1;
    }

    // TODO: Have built-in blueprints such as ape::Blueprints::Sprite
    // which automatically add these components
    auto entity = world.createEntity();
    auto& transform = world.addComponent<ape::Transform>(entity);
    auto& sprite = world.addComponent<ape::Sprite>(entity);
    auto& node = world.addComponent<ape::Node>(entity);
    transform.setPosition(0, 0);
    sprite.setTextureID(spriteTexture, textureStore);
    node.setParent(world, ape::Scene::rootNode);

    while(window.isOpen()) {
        glfwPollEvents();

        auto& transform = world.getComponent<ape::Transform>(entity);
        transform.move(0.01f, 0.f);

        window.clear(ape::Colors::Sky);
        engine.render();
        window.display();
    }

    return 0;
}
