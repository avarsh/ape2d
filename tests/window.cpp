#include <ape/graphics/graphics.h>

int main(int argc, char* argv[])
{
    ape::World world;
    ape::Graphics graphics(world);

    ape::Window& window = graphics.getMainWindow();
    window.create(800, 600, "Window Test");

    graphics.init();

    while(window.isOpen()) {
        glfwPollEvents();

        window.clear(ape::Colors::Sea);
        graphics.draw();
        window.display();
    }

    return 0;
}
