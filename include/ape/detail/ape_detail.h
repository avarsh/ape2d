#ifndef APE_DETAIL_H
#define APE_DETAIL_H

#include <functional>
#include <vector>
#include <chrono>

namespace ape {

    namespace detail {
        using hi_res_clock = std::chrono::high_resolution_clock;
        extern std::vector<std::function<void(double dt)>> simulationCode;

        double getTimeFromPoints(hi_res_clock::time_point t1, hi_res_clock::time_point t2);

        extern const double dt;
        extern hi_res_clock::time_point currentTime;
        extern double accumulator;
    }
}

#endif // APE_DETAIL_H
