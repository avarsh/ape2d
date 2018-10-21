#include <ape/ape.h>

struct ComponentTest : public ape::Component<ComponentTest> {
    ComponentTest(ape::entity_t entity) :
        ape::Component<ComponentTest>(entity) { }
    int x;
};

struct ExclusiveComponent : public ape::Component<ExclusiveComponent> {
    ExclusiveComponent(ape::entity_t entity) :
        ape::Component<ExclusiveComponent>(entity) { }
    // data
};

int main() {

    ape::engine::init();
    ape::window::create(800, 600, "Exclusive Component Test");

    ape::world::setExclusiveComponents<ComponentTest, ExclusiveComponent>();

    auto entity = ape::world::createEntity();
    ape::world::addComponent<ComponentTest>(entity);

    // ape::world::addComponent<ExclusiveComponent>(entity); // ERROR

    while(ape::engine::isRunning()) {
        ape::window::clear(ape::Colors::Red);
        ape::engine::update();
        ape::window::display();
    }

    return 0;
}
