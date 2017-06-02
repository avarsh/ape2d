#include <GLFW/glfw3.h>
#include <ape/utils/frame_counter.h>

namespace ape {
    void FrameCounter::startTimer() {
        glfwSetTime(0);
        start = glfwGetTime();
    }

    double FrameCounter::tick() {
        double current = glfwGetTime();
        double deltaTime = current - start;
        elapsed += deltaTime;
        start = current;
        tickCounter++;

        if(elapsed > 1.f) {
            FPS = tickCounter;
            current = tickCounter = elapsed = 0;
            startTimer();

            counterTickEvent.emit(FPS);
        }

        return deltaTime;
    }

    int FrameCounter::getFPS() {
        return FPS;
    }

    double FrameCounter::getFrameTime() {
        return (1.f / FPS);
    }
}
