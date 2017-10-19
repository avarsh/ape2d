#include <ape/ape.h>

int main() {
    ape::init();
    ape::window::create(800, 600, "Input test");

    auto& context = ape::input::ContextManager::createContext(10);
    auto inputData = ape::input::InputData(
        ape::input::Device::KEYBOARD,
        ape::input::EventType::KEY_PRESS,
        GLFW_KEY_W);

    context.addActionCallback(inputData, [](ape::input::InputData data){
        std::cout << "W key pressed!\n";
    });


    while(ape::window::isOpen()) {
        ape::window::clear(ape::Colors::Slate);
        ape::update();
        ape::window::display();
    }

    ape::window::destroy();
}
