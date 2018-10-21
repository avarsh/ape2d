#include <ape/ape.h>

int main() {
    ape::engine::init();
    ape::window::create(800, 600, "Input test");

    auto& context = ape::input::ContextManager::createContext(10);
    auto actionData = ape::input::ActionData(
        ape::input::Device::KEYBOARD,
        ape::input::ActionType::KEY_PRESS,
        ape::input::Keys::W);

    context.addActionCallback(actionData, [](){
        std::cout << "W key pressed!\n";
    });

    auto stateData = ape::input::StateData(
        ape::input::Device::KEYBOARD,
        ape::input::StateType::KEY_DOWN,
        ape::input::Keys::W);

    context.addStateCallback(stateData, [](){
        std::cout << "W key held down!\n";
    });

    while(ape::engine::isRunning()) {
        ape::window::clear(ape::Colors::Slate);
        ape::engine::update();
        ape::window::display();
    }
}
