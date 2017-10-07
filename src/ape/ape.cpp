#include <ape/ape.h>

namespace ape {
    Engine::Engine() : graphics(world), scene(world) {
        scene.init();
        graphics.window.createdEvent.addCallback([&](Vec2i size){
            glfwSetWindowUserPointer(graphics.window.window, this);
            _onWindowCreated();
        });
    }
    void Engine::render() {
        graphics.begin();
        scene.traverse(graphics);
        graphics.end();
    }

    void Engine::_onWindowCreated() {
        glfwSetKeyCallback(graphics.getWindow().window, _keyCallbackFunc);
    }

    void Engine::_keyCallbackFunc(GLFWwindow* window, int key, int scancode,
                                  int action, int mods) {
        /*
        // For actions
        if(key == GLFW_KEY_UP && action == GLFW_PRESS) {

            std::cout << "Up key pressed!\n";
        }

        // For states
        int state = glfwGetKey(window, GLFW_KEY_UP);
        if (state == GLFW_PRESS)
            std::cout << "Up key held!\n";

        */

       Engine* engine = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window));
       engine->contextManager.notify(key, action);
    }
}
