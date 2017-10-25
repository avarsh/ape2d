#include <ape/ape.h>
#include <random>

int main() {
    ape::init();
    ape::window::create(800, 600, "Sprite Example");

    auto texture = ape::textureStore::loadTexture("examples/images/mario.png");
    if(texture == -1) {
        return 1;
    }

    auto layer1 = ape::world::createEntity();
    auto& node = ape::world::addComponent<ape::Node>(layer1);
    node.setParent(ape::scene::rootNode);

    auto layer2 = ape::world::createEntity();
    auto& node2 = ape::world::addComponent<ape::Node>(layer2);
    node2.setParent(ape::scene::rootNode);

    auto createEntity = [&](float x, float y, ape::entity_t parentNode){
        auto entity = ape::world::createEntity();
        auto& transform = ape::world::addComponent<ape::Transform>(entity);
        auto& sprite = ape::world::addComponent<ape::Sprite>(entity);
        auto& node3 = ape::world::addComponent<ape::Node>(entity);

        transform.setPosition(x, y);
        sprite.setTextureID(texture);
        sprite.scaleBy(3);
        node3.setParent(parentNode);
    };

    createEntity(0, 0, layer1);
    createEntity(50, 0, layer2);

    ape::FrameCounter frames;
    frames.counterTickEvent.addCallback([&](int frames){
        ape::window::setTitle("Sprite Example: " +
            std::to_string(frames) + " fps");
    });

    frames.startTimer();
    while(ape::isRunning()) {
        frames.tick();

        ape::window::clear(ape::Colors::Slate);
        ape::update();
    }

    return 0;
}
