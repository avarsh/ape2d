#include <iostream>
#include <ape/ecs/world.h>
#include <ape/utils/framecounter.h>
#include <ape/graphics/graphics.h>

int main() {

    ape::World world;
    ape::Graphics graphics(world);

    graphics.createWindow(800, 600, "Primitive test");

    auto triangle = world.createEntity();
    world.addComponent<ape::Mesh>(triangle);

    graphics.addVertex(triangle, -0.8f, 1.0f, 0.6f, 0.9f, 0.15f);
    graphics.addVertex(triangle, -0.8f, 0.4f, 1.0f, 0.0f, 0.5f);
    graphics.addVertex(triangle, 0.0f, 0.8f, 0.2f, 0.3f, 0.9f);

    auto square = world.createEntity();
    graphics.createRectangle(square, 0.0, 0.0, 0.5, 0.5);
    graphics.setFillColor(square, 0.5f, 0.1f, 0.2f);

    int counter = 0;

    ape::FrameCounter frames;

    frames.counterTickEvent.addCallback([](int FPS){
        std::cout << FPS << std::endl;
    });

    frames.startTimer();
    double deltaTime;

    while(graphics.windowIsOpen()) {

        glfwPollEvents();
        deltaTime = frames.calculateFPS();

        graphics.clearWindow(0.3, 0.3, 0.4);
        graphics.displayWindow();

        if(counter == 2) {
            auto pentagon = world.createEntity();
            world.addComponent<ape::Mesh>(pentagon);

            graphics.addVertex(pentagon, 0.5f, 0.5f);
            graphics.addVertex(pentagon, 0.1f, 0.3f, 0.7f, 0.19f, 0.06f);
            graphics.addVertex(pentagon, 0.3f, 0.1f, 0.11f, 0.25f, 0.78f);
            graphics.addVertex(pentagon, 0.7f, 0.1f, 0.96f, 0.99f, 0.11f);
            graphics.addVertex(pentagon, 0.9f, 0.3f, 1.0f, 0.98f, 0.67f);

            graphics.setVertexColor(pentagon, 0, 1.f, 0.f, 0.f);

            counter++;
        }

        graphics.move(triangle, ape::Vec2<GLfloat>(deltaTime * 0.2, 0));
    }

    return 0;
}
