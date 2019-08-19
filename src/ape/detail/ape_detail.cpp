#include <ape/detail/ape_detail.h>
#include <iostream>

namespace ape {
    namespace detail {
        double getTimeFromPoints(hi_res_clock::time_point t1, hi_res_clock::time_point t2) {
            std::chrono::duration<double> timeSpan =
                std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

            return timeSpan.count();
        }

        bool running = false;
        const double dt = 0.01;
        std::vector<std::function<void(double dt)>> simulationCode;
        hi_res_clock::time_point currentTime;
        double accumulator;

        uint32_t SDLWindowResized;
    }
}