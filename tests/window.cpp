#include <ape/graphics/graphics.h>

int main(int argc, char* argv[])
{
    ape::World world;
    ape::Graphics graphics(world);

    graphics.createWindow(800, 600, "Window Test");

    while(graphics.windowIsOpen()) {
        glfwPollEvents();

        graphics.clearWindow(ape::Colors::Sea);
        graphics.displayWindow();
    }

    return 0;
}
