#include <ape/ape.h>

int main() {
    ape::engine::init();
    ape::window::create(800, 600, "Test window");

    while(ape::engine::isRunning()) {
        ape::window::clear(ape::Colors::Orange);
        ape::engine::update();
        ape::window::display();
    }

    return 0;
}
