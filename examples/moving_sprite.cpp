#include <ape/ape.h>

int main() {
    ape::engine::init();
    ape::window::create(800, 600, "Controllable Sprite");

    auto texture = ape::textureStore::loadTexture("./examples/images/mario.png");
    if(texture == -1) {
        return 1;
    }

    auto player = ape::world::createEntity();
    auto& transform = ape::world::getComponent<ape::Transform>(player);
    transform.setPosition(0, 0);
    auto& sprite = ape::world::addComponent<ape::Sprite>(player, texture);
    auto& node = ape::world::addComponent<ape::Node>(player, ape::scene::rootNode);

    // Set up inputs
    auto& context = ape::input::ContextManager::createContext(0);
    std::map<int, ape::Vec2f> keys = {
        {ape::input::Keys::W, ape::Vec2f(0, -100)},
        {ape::input::Keys::D, ape::Vec2f(100, 0)},
        {ape::input::Keys::S, ape::Vec2f(0, 100)},
        {ape::input::Keys::A, ape::Vec2f(-100, 0)}
    };

    std::map<int, int> dirs = {
        {ape::input::Keys::W, 1},
        {ape::input::Keys::D, 0},
        {ape::input::Keys::S, 1},
        {ape::input::Keys::A, 0}
    };

    for(auto const& key : keys) {
        ape::input::StateData pressed(
            ape::input::Device::KEYBOARD,
            ape::input::StateType::KEY_DOWN,
            key.first
        );

        context.addStateCallback(pressed, [&](){
            auto& transform = ape::world::getComponent<ape::Transform>(player);
            auto current = transform.getVelocity();
            if(dirs[key.first] == 0) {transform.setVelocity(key.second.x, current.y);}
            if(dirs[key.first] == 1) {transform.setVelocity(current.x, key.second.y);}
        });

        ape::input::ActionData released(
            ape::input::Device::KEYBOARD,
            ape::input::ActionType::KEY_RELEASE,
            key.first
        );

        context.addActionCallback(released, [&](){
            auto& transform = ape::world::getComponent<ape::Transform>(player);
            auto current = transform.getVelocity();
            if(dirs[key.first] == 0) { transform.setVelocity(0, current.y); }
            if(dirs[key.first] == 1) { transform.setVelocity(current.x, 0); }
        });
    }

    while(ape::engine::isRunning()) {
        ape::window::clear(ape::Colors::Slate);
        ape::engine::update();
        ape::window::display();
    }

    return 0;
}
