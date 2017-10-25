#ifndef APE_H
#define APE_H

#include <ape/core/world.h>
#include <ape/graphics/graphics.h>
#include <ape/graphics/window.h>
#include <ape/core/transform.h>
#include <ape/scene/scene.h>
#include <ape/utils/frame_counter.h>
#include <ape/input/input_system.h>
#include <ape/detail/ape_detail.h>

#include <chrono>

namespace ape {
    void init();
    void update();
    void addSimulationCode(std::function<void(double dt)> function);
    bool isRunning();
}

#endif // APE_H
