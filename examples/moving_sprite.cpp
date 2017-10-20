#include <ape/ape.h>

int main() {
    ape::init();
    ape::window::create(800, 600, "Controllable Sprite");

    auto texture = ape::textureStore::loadTexture("./examples/images/mario.png");
    if(texture == -1) {
        return 1;
    }

    auto player = ape::world::createEntity();
    auto& transform = ape::world::addComponent<ape::Transform>(player);
    auto& sprite = ape::world::addComponent<ape::Sprite>(player);
    auto& node = ape::world::addComponent<ape::Node>(player);

    transform.setPosition(100, 100);
    sprite.setTextureID(texture);
    node.setParent(ape::scene::rootNode);

    // Set up inputs
    auto& context = ape::input::ContextManager::createContext(0);
    std::map<int, ape::Vec2f> keys = {
        {GLFW_KEY_W, ape::Vec2f(0, -0.01)},
        {GLFW_KEY_D, ape::Vec2f(0.01, 0)},
        {GLFW_KEY_S, ape::Vec2f(0, 0.01)},
        {GLFW_KEY_A, ape::Vec2f(-0.01, 0)}
    };

    for(auto const& key : keys) {
        ape::input::StateData data(
            ape::input::Device::KEYBOARD,
            ape::input::StateType::KEY_DOWN,
            key.first
        );

        context.addStateCallback(data, [&](){
            auto& transform = ape::world::getComponent<ape::Transform>(player);
            transform.move(key.second.x, key.second.y);
        });
    }

    while(ape::window::isOpen()) {
        ape::window::clear(ape::Colors::Slate);
        ape::update();
        ape::window::display();
    }
}
