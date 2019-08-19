#ifndef APE_DETAIL_H
#define APE_DETAIL_H

#include <chrono>
#include <vector>
#include <functional>
#include <SDL2/SDL.h>
#include <queue>

namespace ape {
    namespace detail {
        using hi_res_clock = std::chrono::high_resolution_clock;
        // Get time span between two points in time
        double getTimeFromPoints(hi_res_clock::time_point t1, hi_res_clock::time_point t2);

        extern const double dt; // The timestep - may allow this to be changed
        // Time point to use for calculating deltas
        extern hi_res_clock::time_point currentTime;
        // Custom user code to run in fixed timestep mode
        extern std::vector<std::function<void(double dt)>> simulationCode;
        // An accumulator to keep track of frame time not simulated
        extern double accumulator;
        // Whether the engine is running.
        extern bool running;
    }
}

#endif