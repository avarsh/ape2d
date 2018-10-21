#define NDEBUG
#include <ape/ape.h>
#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std::chrono;

int main() {

    ape::engine::init();
    ape::window::create(800, 600, "Iteration speed test");

    for(int i = 0; i < 10000; i++) {
        auto entity = ape::world::createEntity();
        auto& sprite = ape::world::addComponent<ape::Sprite>(entity);
        auto& transform = ape::world::getComponent<ape::Transform>(entity);
        transform.setPosition(rand() % 1000, rand() % 1000);
    }

    high_resolution_clock::time_point start = high_resolution_clock::now();

    for(auto& sprite : ape::world::getComponentList<ape::Sprite>()) {
        if(ape::world::entityHasComponent<ape::Transform>(sprite.getEntity())) {
            auto& transform = ape::world::getComponent<ape::Transform>(sprite.getEntity());
            auto pos = transform.getPosition();
            if(pos.x < 0 || pos.x > 500 || pos.y < 0 || pos.y > 500) {
                // CODE
            }
        }
    }

    high_resolution_clock::time_point end = high_resolution_clock::now();

    duration<double> timeSpan = duration_cast<duration<double>>(end - start);

    std::cout << timeSpan.count() << " seconds taken\n";

    while(ape::engine::isRunning()) {
        ape::engine::update();
        ape::window::display();
    }

    return 0;
}
