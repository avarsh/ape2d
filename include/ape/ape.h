#ifndef APE_H
#define APE_H

#include <ape/graphics/graphics.h>
#include <ape/core/world.h>
#include <ape/utils/frame_counter.h>
#include <ape/core/transform.h>

namespace ape {

    class Engine {
    public:
        Engine();

        Graphics& getGraphics();
        World& getWorld();
    private:
        Graphics graphics;
        World world;
    };
}

#endif
