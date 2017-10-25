#ifndef APE_DETAIL_H
#define APE_DETAIL_H

#include <functional>
#include <vector>
#include <chrono>

namespace ape {

    namespace detail {
        using hi_res_clock = std::chrono::high_resolution_clock;
        // Custom user code to run in fixed timestep mode
        extern std::vector<std::function<void(double dt)>> simulationCode;

        // Get time span between two points in time
        double getTimeFromPoints(hi_res_clock::time_point t1, hi_res_clock::time_point t2);

        extern const double dt; // The timestep - may allow this to be changed
        // Time point to use for calculating deltas
        extern hi_res_clock::time_point currentTime;
        // An accumulator to keep track of frame time not simulated
        extern double accumulator;
    }
}

#endif // APE_DETAIL_H
