#ifndef APE_H
#define APE_H

#include <ape/graphics/graphics.h>
#include <ape/core/world.h>
#include <ape/utils/frame_counter.h>
#include <ape/core/transform.h>
#include <ape/core/scene.h>
#include <ape/input/context_manager.h>

namespace ape {

    class Engine {
    public:
        Engine();

        void render();

        Graphics graphics;
        Scene scene;
        World world;
        ContextManager contextManager;
    private:
        void _onWindowCreated();
        static void _keyCallbackFunc(GLFWwindow* window, int key, int scancode,
                                     int action, int mods);
    };
}

#endif
