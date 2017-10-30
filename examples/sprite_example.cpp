#include <ape/ape.h>
#include <random>

int main() {
    ape::init();
    ape::window::create(800, 600, "Sprite Example");

    auto texture = ape::textureStore::loadTexture("examples/images/mario.png");
    if(texture == -1) {
        return 1;
    }

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> xDist(0,760);
    std::uniform_int_distribution<int> yDist(0,506);

    for(int i = 0; i < 1000; i++) {
        auto entity = ape::world::createEntity();
        auto& transform = ape::world::getComponent<ape::Transform>(entity);
        transform.setPosition(xDist(rng), yDist(rng));
        auto& sprite = ape::world::addComponent<ape::Sprite>(entity);
        sprite.setTextureID(texture);
    }

    ape::FrameCounter frames;
    frames.counterTickEvent.addCallback([&](int frames){
        ape::window::setTitle("Sprite Example: " +
            std::to_string(frames) + " fps");
    });

    frames.startTimer();
    while(ape::isRunning()) {
        ape::update();
        frames.tick();

        ape::window::clear(ape::Colors::Slate);
        ape::graphics::begin();
        for(auto& sprite : ape::world::getComponentList<ape::Sprite>()) {
            ape::graphics::draw(&sprite);
        }
        ape::graphics::end();
        ape::window::display();
    }

    return 0;
}
