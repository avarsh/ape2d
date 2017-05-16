#include <iostream>
#include <ape/ecs/world.h>
#include <ape/graphics/graphics.h>

int main() {

    ape::Graphics graphics;
    ape::World world;

    graphics.createWindow(800, 600, "Primitive test");

    auto triangle = world.createEntity();
    auto& triangleMesh = world.addComponent<ape::Mesh>(triangle);

    graphics.addVertex(world, triangle, -0.8f, 1.0f, 0.6f, 0.9f, 0.15f);
    graphics.addVertex(world, triangle, -0.8f, 0.4f, 1.0f, 0.0f, 0.5f);
    graphics.addVertex(world, triangle, 0.0f, 0.8f, 0.2f, 0.3f, 0.9f);

    auto square = world.createEntity();
    auto& squareMesh = world.addComponent<ape::Mesh>(square);

    graphics.addVertex(world, square, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f);
    graphics.addVertex(world, square, 0.0f, -0.5f, 0.4f, 0.6f, 0.5f);
    graphics.addVertex(world, square, 0.5f, -0.5f, 0.2f, 0.3f, 0.9f);
    graphics.addVertex(world, square, 0.5f, 0.0f, 0.6f);

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

            counter += counter != 6 ? 1 : 0;
        }


        glfwPollEvents();

        graphics.clearWindow(0.3, 0.3, 0.4);
        graphics.displayWindow(world);

        if(counter == 5) {
            std::cout << "added!\n";
            auto pentagon = world.createEntity();
            auto& pMesh = world.addComponent<ape::Mesh>(pentagon);

            graphics.addVertex(world, pentagon, 0.5f, 0.5f, 1.0f, 0.9f, 0.6f);
            graphics.addVertex(world, pentagon, 0.1f, 0.3f, 0.7f, 0.19f, 0.06f);
            graphics.addVertex(world, pentagon, 0.3f, 0.1f, 0.11f, 0.25f, 0.78f);
            graphics.addVertex(world, pentagon, 0.7f, 0.1f, 0.96f, 0.99f, 0.11f);
            graphics.addVertex(world, pentagon, 0.9f, 0.3f, 1.0f, 0.98f, 0.67f);

            counter++;
        }

        frameCount++;
    }

    return 0;
}
