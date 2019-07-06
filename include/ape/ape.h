#ifndef APE_H
#define APE_H

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
     * Cleans up all systems and resources
     */

    void destroy();
}

#endif 