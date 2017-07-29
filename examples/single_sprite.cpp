 #include <ape/ape.h>
#include <ape/core/world.h>

int main() {
    ape::Engine engine;
    auto& graphics = engine.getGraphics();
    auto& window = graphics.getWindow();
    auto& world = engine.getWorld();

    window.create(600, 600, "Single Sprite Example");

    ape::Material spriteTexture;
    spriteTexture.loadTexture("examples/images/mario.png");

    ape::Material luigiTex;
    luigiTex.loadTexture("examples/images/luigi.png");

    // TODO: Have built-in blueprints such as ape::Blueprints::Sprite
    // which automatically add these components
    auto entity = world.createEntity();
    auto& transform = world.addComponent<ape::Transform>(entity);
    auto& sprite = world.addComponent<ape::Sprite>(entity);
    transform.setPosition(0, 0);
    sprite.setMaterial(&spriteTexture);

    while(window.isOpen()) {
        glfwPollEvents();

        auto& transform = world.getComponent<ape::Transform>(entity);
        transform.move(0.00001f, 0.f);

        window.clear(ape::Colors::Sky);

        graphics.begin();
        for(auto& sprite : world.getComponentList<ape::Sprite>()) {
            graphics.draw(&sprite);
        }
        graphics.end();

        window.display();
    }

    return 0;
}
