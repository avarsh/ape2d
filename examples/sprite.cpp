#include <ape/ape.h>

int main(int argc, char* argv[])
{
    ape::Engine engine;
    ape::Graphics& graphics = engine.getGraphics();
    ape::Window& window = graphics.getWindow();
    ape::World& world = engine.getWorld();

    window.create(800, 600, "Sprites!");

    ape::Texture backgroundTexture;
    ape::Texture spriteTexture;

    try {
        backgroundTexture = graphics.loadTexture("./data/background.png");
        spriteTexture = graphics.loadTexture("./data/sprite.png");
    } catch (std::runtime_error err) {
        std::cout << err.what() << std::endl;
        return 1;
    }

    auto background = world.createEntity();
    auto& transform = world.addComponent<ape::Transform>(background);
    auto& mesh = world.addComponent<ape::Mesh>(background);

    mesh.setTexture(backgroundTexture);

    auto sprite = world.createEntity();
    auto& transform2 = world.addComponent<ape::Transform>(sprite);
    auto& mesh2 = world.addComponent<ape::Mesh>(sprite);

    mesh2.setTexture(spriteTexture);

    while(window.isOpen()) {
        engine.pollEvents();

        graphics.clear(ape::Colors::Sky);
        graphics.draw(background);
        graphics.draw(sprite);
        graphics.display();
    }

    return 0;
}
