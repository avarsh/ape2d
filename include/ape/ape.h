#ifndef APE_H
#define APE_H

#include <ape/detail/ape_detail.h>
#include <ape/graphics/graphics.h>
#include <ape/scene/detail/scene_detail.h>
#include <ape/graphics/texture_store.h>
#include <ape/graphics/window.h>
#include <ape/core/world.h>
#include <ape/input/context.h>
#include <ape/input/detail/input_detail.h>

namespace ape {
    /**
     * Initializes the engine.
     */
    void init();

    /**
     * Whether the game is running.
     */
    bool isRunning();

    /**
     * Updates the game.
     */
    void update();

    /**
     * Adds code to be executed during the physics simulation.
     */
    void addSimulationCode(std::function<void(double dt)> function);

    /**
     * Cleans up all systems and resources
     */
    void destroy();
}

#endif 