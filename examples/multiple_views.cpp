#include <ape/ape.h>

int main() {

    ape::engine::init();
    ape::window::create(800, 600, "Multiple Views");

    auto secondCamera = ape::world::createEntity();
    ape::world::addComponent<ape::Transform>(secondCamera, 0, 0);
    auto& camera = ape::world::addComponent<ape::Camera>(secondCamera);
    camera.setViewport(ape::FloatRect(0.5, 0, 0.5, 1));

    auto& defaultCam = ape::world::getComponent<ape::Camera>(ape::scene::defaultCamera);
    defaultCam.setViewport(ape::FloatRect(0, 0, 0.5, 1));

    auto mario = ape::textureStore::loadTexture("./examples/images/mario.png");
    auto luigi = ape::textureStore::loadTexture("./examples/images/luigi.png");
    if(mario == -1 || luigi == -1) {
        return 1;
    }

    // Create the two players
    auto player1 = ape::world::createEntity();
    ape::world::addComponent<ape::Transform>(player1, 0, 0);
    ape::world::addComponent<ape::Sprite>(player1, mario);
    ape::world::addComponent<ape::Node>(player1, ape::scene::rootNode);

    auto player2 = ape::world::createEntity();
    ape::world::addComponent<ape::Transform>(player2, 0, 0);
    auto& sprite = ape::world::addComponent<ape::Sprite>(player2, luigi);
    sprite.scaleBy(0.2f);
    auto& node = ape::world::addComponent<ape::Node>(player2, ape::scene::rootNode);
    node.setCamera(secondCamera);

    while(ape::engine::isRunning()) {
        ape::window::clear(ape::Colors::Slate);
        ape::engine::update();
        ape::window::display();
    }

    return 0;
}
