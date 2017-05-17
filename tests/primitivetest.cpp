#include <iostream>
#include <ape/ecs/world.h>
#include <ape/graphics/graphics.h>

int main() {

    ape::World world;
    ape::Graphics graphics(world);

    graphics.createWindow(800, 600, "Primitive test");

    auto triangle = world.createEntity();
    world.addComponent<ape::Mesh>(triangle);

    graphics.addVertex(triangle, -0.8f, 1.0f, 0.6f, 0.9f, 0.15f);
    float pos1 = -0.8f;
    graphics.addVertex(triangle, -0.8f, 0.4f, 1.0f, 0.0f, 0.5f);
    float pos2 = -0.8f;
    graphics.addVertex(triangle, 0.0f, 0.8f, 0.2f, 0.3f, 0.9f);
    float pos3 = 0.0f;

    auto square = world.createEntity();
    world.addComponent<ape::Mesh>(square);

    graphics.addVertex(square, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f);
    graphics.addVertex(square, 0.0f, -0.5f, 0.4f, 0.6f, 0.5f);
    graphics.addVertex(square, 0.5f, -0.5f, 0.2f, 0.3f, 0.9f);
    graphics.addVertex(square, 0.5f, 0.0f, 0.6f);

    double start = glfwGetTime();
    double elapsed = 0;
    int frameCount = 0;

    int counter = 0;
    while(graphics.windowIsOpen()) {
        double current = glfwGetTime();
        elapsed += current - start;
        start = current;

        if(elapsed > 1.f) {
            std::cout << frameCount << std::endl;
            frameCount = 0;
            elapsed = 0;

            counter++;
        }


        glfwPollEvents();

        graphics.clearWindow(0.3, 0.3, 0.4);
        graphics.displayWindow(world);

        if(counter == 5) {
            auto pentagon = world.createEntity();
            world.addComponent<ape::Mesh>(pentagon);

            graphics.addVertex(pentagon, 0.5f, 0.5f);
            graphics.addVertex(pentagon, 0.1f, 0.3f, 0.7f, 0.19f, 0.06f);
            graphics.addVertex(pentagon, 0.3f, 0.1f, 0.11f, 0.25f, 0.78f);
            graphics.addVertex(pentagon, 0.7f, 0.1f, 0.96f, 0.99f, 0.11f);
            graphics.addVertex(pentagon, 0.9f, 0.3f, 1.0f, 0.98f, 0.67f);

            graphics.setVertexColour(pentagon, 0, 1.f, 0.f, 0.f);

            counter++;
        }

        pos1 += 0.0001;
        pos2 += 0.0001;
        pos3 += 0.0001;

        graphics.setVertexPosition(triangle, 0, pos1, 1.0f);
        graphics.setVertexPosition(triangle, 1, pos2, 0.4f);
        graphics.setVertexPosition(triangle, 2, pos3, 0.8f);

        frameCount++;
    }

    return 0;
}
