#include <iostream>
#include <cstdlib>
#include <ape/ecs/world.h>
#include <ape/graphics/graphics.h>

struct {
    ape::Event<double, double> vertexAdd;
    ape::Event<> newPolygon;
} programEvents;

void onMouseClick(GLFWwindow* window, int button, int action, int mods) {
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        programEvents.vertexAdd.emit(x, y);
    }

    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        programEvents.newPolygon.emit();
    }
}

int main(int argc, char* argv[])
{
    ape::World world;
    ape::Graphics graphics(world);

    graphics.createWindow(800, 600, "Mouse test");

    glfwSetMouseButtonCallback(graphics.getWindow(), onMouseClick);

    auto current = world.createEntity();
    world.addComponent<ape::Mesh>(current);

    programEvents.vertexAdd.addCallback([&](double x, double y){
        graphics.addVertex(current, (x - 400) / 400, (y - 300) / -300,
            ((double) rand() / (RAND_MAX)) , ((double) rand() / (RAND_MAX)) , ((double) rand() / (RAND_MAX)));
    });

    programEvents.newPolygon.addCallback([&](){
        current = world.createEntity();
        world.addComponent<ape::Mesh>(current);
    });

    while(graphics.windowIsOpen()) {
        glfwPollEvents();

        graphics.clearWindow(1.0f, 1.0f, 1.0f);

        graphics.displayWindow();
    }

    return 0;
}
