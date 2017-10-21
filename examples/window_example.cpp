#include <ape/ape.h>

int main() {
    ape::init();
    ape::window::create(800, 600, "Test window");

    while(ape::window::isOpen()) {
        glfwPollEvents();

        ape::window::clear(ape::Colors::Orange);
        ape::update();
    }

    ape::window::destroy();
}
