#ifndef APE_H
#define APE_H

#include <ape/core/world.h>
#include <ape/graphics/graphics.h>
#include <ape/core/transform.h>

namespace ape {

    class Engine {
    public:
        Engine();

        Graphics& getGraphics();

        World& getWorld();

        void pollEvents();
    private:
        World world;
        Graphics graphics;
    };
}

#endif // APE_H
