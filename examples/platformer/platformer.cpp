#include <ape/ape.h>
#include <iostream>

// A simple custom component
class Friction : public ape::Component<Friction> {
    public:
        Friction(ape::entity_t entity) : ape::Component<Friction>(entity) { }
        float mu;

};

// Implement a system to apply friction to objects - all entities by default
// have a transform component, so we do not need to check this.
void frictionSystem() {
    for (auto& frictionComp : ape::world::getComponentPool<Friction>()) {
        auto& transform = ape::world::getComponent<ape::Transform>(frictionComp.getEntity());
        int sign = transform.velocity.x < 0 ? 1 : -1;
        transform.velocity.x -= transform.velocity.x * frictionComp.mu;
    }
}

int main() {
    // Initialise the engine
    ape::init();
    ape::window::create(800, 600, "Platformer");

    // Load a character
    ape::texture_id_t playerTexture = ape::TextureStore::loadTexture("./examples/platformer/p1_stand.png");

    // Create main character
    ape::entity_t player = ape::world::createEntity();

    // First we add a sprite component using the player texture
    auto& sprite = ape::world::addComponent<ape::Sprite>(player);
    sprite.textureId = playerTexture;
    sprite.textureRect.origin = ape::Vec2i(0, 0);
    sprite.textureRect.size = ape::TextureStore::getTextureSize(playerTexture);

    // Then we add the player to the scene
    auto& node = ape::world::addComponent<ape::Node>(player);
    auto& root = ape::world::getComponent<ape::Node>(ape::scene::ROOT_NODE);
    root.addChild(player);

    // Finally we add our own custom component which applies friction to the player
    auto& friction = ape::world::addComponent<Friction>(player);
    friction.mu = 0.05;

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

    info.info.keyCode = ape::input::KeyCode::LEFT;
    ape::input::addCallback(mainContext, info, [player](ape::input::InputEventInfo info) {
            auto& transform = ape::world::getComponent<ape::Transform>(player);
            transform.velocity.x += transform.velocity.x < -200 ? 0 : -10.f;
            return false;
        }
    );
    
    // Custom physics, including some notion of gravity and applying friction
    ape::addSimulationCode([player](double dt) {
        ape::Transform& playerTransform = ape::world::getComponent<ape::Transform>(player);
        playerTransform.velocity.y += 400.f * dt;
        if (playerTransform.position.y >= 200) {
            playerTransform.velocity.y = 0;
        }

        frictionSystem();
    });

    ape::run(ape::Colors::Slate);

    ape::destroy();
    return 0;
}
