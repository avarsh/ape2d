#include <ape/ape.h>

int main() {
    ape::Engine engine;
    auto& world = engine.getWorld();
    auto& window = engine.getGraphics().getWindow();
    auto& textureStore = engine.getGraphics().getTextureStore();

    window.create(800, 600, "Layer Example");

    auto layer1 = world.createEntity();
    auto& node = world.addComponent<ape::Node>(layer1);
    node.setParent(world, ape::Scene::rootNode);

    auto layer2 = world.createEntity();
    auto& node2 = world.addComponent<ape::Node>(layer2);
    node2.setParent(world, ape::Scene::rootNode);

    auto spriteTexture = textureStore.loadTexture("examples/images/mario.png");

    auto createEntity = [&](float x, float y, ape::entity_t parentNode){
        auto entity = world.createEntity();
        auto& transform = world.addComponent<ape::Transform>(entity);
        auto& sprite = world.addComponent<ape::Sprite>(entity);
        auto& node3 = world.addComponent<ape::Node>(entity);

        transform.setPosition(x, y);
        sprite.setTextureID(spriteTexture, textureStore);
        sprite.scaleBy(3);
        node3.setParent(world, parentNode);
    };

    createEntity(0, 0, layer1);
    createEntity(50, 0, layer2);

    // Push the first layer on top of the second layer for whatever reason
    // Now layer2 has index 0 and layer1 has index 1 so it will be rendered
    // after layer2
    world.getComponent<ape::Node>(layer1).setIndex(world, 1);

    while(window.isOpen()) {
        glfwPollEvents();

        window.clear(ape::Colors::Sea);
        engine.render();
        window.display();
    }
}
