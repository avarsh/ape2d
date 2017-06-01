#include <ape/ape.h>

int main(int argc, char* argv[])
{
    ape::Engine engine;
    ape::Graphics& graphics = engine.getGraphics();
    ape::Window& window = graphics.getWindow();

    window.create(800, 600, "Window Creation Example");

    while(window.isOpen()) {
        engine.pollEvents();

        graphics.clear(ape::Colors::Slate);
        graphics.display();
    }

    return 0;
}
