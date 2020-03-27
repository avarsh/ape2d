#include <ape/ape.h>
#include <iostream>

int main() {
    // Initialise the engine
    ape::init();
    ape::window::create(800, 600, "Platformer");

    // Load a character
    ape::texture_id_t playerTexture = ape::TextureStore::loadTexture("./examples/p1_stand.png");

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
    ape::context_t mainContext = ape::input::createContext(10);
    ape::input::InputEventInfo info;
    info.inputType = ape::input::InputType::STATE;
    info.eventType = ape::input::EventType::KEY_PRESS;
    info.info.keyCode = ape::input::KeyCode::RIGHT;
    ape::input::addCallback(mainContext, info, [player](ape::input::InputEventInfo info) {
            auto& transform = ape::world::getComponent<ape::Transform>(player);
            transform.velocity.x += transform.velocity.x > 200 ? 0 : 10.f;
            return false;
        }
    );

    info.inputType = ape::input::InputType::ACTION;
    info.eventType = ape::input::EventType::KEY_UP;
    ape::input::addCallback(mainContext, info, [player](ape::input::InputEventInfo info) {
            ape::world::getComponent<ape::Transform>(player).velocity.x = 0;
            return false;
        }
    );
    
    ape::addSimulationCode([player](double dt) {
        ape::Transform& playerTransform = ape::world::getComponent<ape::Transform>(player);
        playerTransform.velocity.y += 400.f * dt;
        if (playerTransform.position.y >= 200) {
            playerTransform.velocity.y = 0;
        }
    });

    ape::run(ape::Colors::Slate);

    ape::destroy();
    return 0;
}
