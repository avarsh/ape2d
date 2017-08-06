#ifndef APE_H
#define APE_H

#include <ape/graphics/graphics.h>
#include <ape/core/world.h>
#include <ape/utils/frame_counter.h>
#include <ape/core/transform.h>
#include <ape/core/scene.h>

namespace ape {

    class Engine {
    public:
        Engine();

        void render();

        Graphics& getGraphics();
        World& getWorld();
        Scene& getScene();
    private:
        Graphics graphics;
        Scene scene;
        World world;
    };
}

#endif
