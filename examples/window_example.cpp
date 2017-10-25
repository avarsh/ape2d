#include <ape/ape.h>

int main() {
    ape::init();
    ape::window::create(800, 600, "Test window");

    while(ape::isRunning()) {
        ape::window::clear(ape::Colors::Orange);
        ape::update();
    }

    return 0;
}
