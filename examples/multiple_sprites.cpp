#include <ape/ape.h>
#include <ape/core/world.h>
#include <cstdlib>

int main() {
    ape::Engine engine;
    auto& graphics = engine.getGraphics();
    auto& window = graphics.getWindow();
    auto& world = engine.getWorld();

    window.create(600, 600, "Sprite Batching Example");

    ape::Material marioTex;
    marioTex.loadTexture("examples/images/mario.png");

    ape::Material luigiTex;
    luigiTex.loadTexture("examples/images/luigi.png");

    // TODO: Have built-in blueprints such as ape::Blueprints::Sprite
    // which automatically add these components
    int num = 1000;
    for(int i = 0; i < num; i++) {

	    float r = (float)rand() / (float)RAND_MAX;
        float posX = -1 + r * 2;
        r = (float)rand() / (float)RAND_MAX;
        float posY = -1 + r * 2;

        auto entity = world.createEntity();
        auto& transform = world.addComponent<ape::Transform>(entity);
        auto& sprite = world.addComponent<ape::Sprite>(entity);

        transform.setPosition(posX, posY);

        /*
        // Swap materials half way through
        if(i >= (num / 2)) {
            sprite.setMaterial(&marioTex);
        } else {
            sprite.setMaterial(&luigiTex);
        }*/

        // Swap materials every sprite
        if(i % 2 == 0) {
            sprite.setMaterial(&marioTex);
        } else {
            sprite.setMaterial(&luigiTex);
        }
    }

    ape::FrameCounter frames;
    frames.counterTickEvent.addCallback([&window](int frames) {
        window.setTitle("Sprite Batching Example: " + std::to_string(frames));
    });

    frames.startTimer();

    while(window.isOpen()) {
        glfwPollEvents();
        frames.tick();

        window.clear(ape::Colors::Sky);

        graphics.begin();
        int i = 0;
        for(auto& sprite : world.getComponentList<ape::Sprite>()) {
            graphics.draw(&sprite);
            i++;
        }

        graphics.end();

        window.display();
    }

    return 0;
}
