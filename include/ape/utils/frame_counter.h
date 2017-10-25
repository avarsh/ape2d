#ifndef FRAME_COUNTER_H
#define FRAME_COUNTER_H

#include <ape/core/event.h>

namespace ape {

    /**
     * Simple utility class to calculate the frames per second count
     * for the application.
     */
    class FrameCounter {
    public:

        /**
         * Starts the timer, resetting the clock to 0.
         */
        void startTimer();

        /**
         * Calculates the FPS by getting the time elapsed since the
         * previous clock call.
         * @return The time delta between the two clocks.
         */
        double tick();

        /**
         * Gets the last known value for the FPS.
         * @return An integer value for the FPS.
         */
        int getFPS();

        /**
         * Gets the average length of one frame.
         * @return A double precision value containign the length of a frame.
         */
        double getFrameTime();

        /**
         * An event emitted every second, when a new FPS value is calculated.
         */
        Event<int> counterTickEvent;
    private:
        double start {0.0};
        double elapsed {0.0};

        int FPS {0};

        int tickCounter {0};
        double frameTime {0};
    };
}

#endif
