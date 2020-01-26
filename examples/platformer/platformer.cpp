#include <ape/ape.h>
#include <iostream>

int main() {
    // Initialise the engine
    ape::init();
    ape::window::create(800, 600, "Platformer");

    // Load a character
    ape::texture_id_t playerTexture = ape::TextureStore::loadTexture("./assets/Player/p1_stand.png");

    // Create main character
    ape::entity_t player = ape::world::createEntity();
    auto& sprite = ape::world::addComponent<ape::Sprite>(player);
    sprite.textureId = playerTexture;
    sprite.textureRect.origin = ape::Vec2i(0, 0);
    sprite.textureRect.size = ape::TextureStore::getTextureSize(playerTexture);

    auto& node = ape::world::addComponent<ape::Node>(player);
    auto& root = ape::world::getComponent<ape::Node>(ape::scene::ROOT_NODE);
    root.addChild(player);

    // Set up keybinds
//    ape::input::Context mainContext = ape::input::Context(1, "./examples/platformer/contexts/main.json");
//    mainContext.load();
//
//    mainContext.addCallback("jump", [](ape::input::InputEventInfo info){
//        std::cout << "Jump!\n";
//
//        return false;
//    });
//
//    mainContext.addCallback("move_left", [](ape::input::InputEventInfo info){
//        std::cout << "Left!\n";
//
//        return false;
//    });
//
//    mainContext.addCallback("move_right", [](ape::input::InputEventInfo info){
//        std::cout << "Right!\n";
//
//        return false;
//    });

    while (ape::isRunning()) {
        ape::update();
    }

    ape::destroy();
    return 0;
}
