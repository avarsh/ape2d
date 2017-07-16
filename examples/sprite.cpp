#include <ape/ape.h>

int main(int argc, char* argv[])
{
    ape::Engine engine;
    ape::Graphics& graphics = engine.getGraphics();
    ape::Window& window = graphics.getWindow();
    ape::World& world = engine.getWorld();

    window.create(800, 600, "Sprites!");

    ape::Texture textures[2];
    std::string textureSources[] = {
        "./examples/images/car.png",
        "./examples/images/post.png"
    };

    try {
        for(int i = 0; i < 2; i++) {
            textures[i] = graphics.loadTexture(textureSources[i]);
        }
    } catch (std::runtime_error err) {
        std::cout << err.what() << std::endl;
        return 1;
    }

    int count = 0;
    while(count < 5) {
        for(int j = 1; j < 3; j++) {
            auto entity = world.createEntity();
            auto& transform = world.addComponent<ape::Transform>(entity);
            auto& mesh = world.addComponent<ape::Mesh>(entity);

            mesh.setTexture(textures[j - 1]);

            transform.setPosition(count * j * 10, count * j * 10);
        }

        count++;
    }

    ape::FrameCounter counter;

    auto callback = [&window](int fps) {
        window.setTitle("Sprites! Running at: " + std::to_string(fps) + " FPS");
    };

    counter.counterTickEvent.addCallback(callback);
    counter.startTimer();

    while(window.isOpen()) {
        engine.pollEvents();
        counter.tick();

        graphics.clear(ape::Colors::Sea);

        for(auto& mesh : world.getComponentList<ape::Mesh>()) {
            world.getComponent<ape::Transform>(mesh.entity).move(0.01, 0.01);
            graphics.draw(mesh.entity);
        }

        graphics.display();
    }

    return 0;
}
