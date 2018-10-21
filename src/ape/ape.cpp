#include <ape/ape.h>

namespace ape::engine {
    using hi_res_clock = std::chrono::high_resolution_clock;
    void init() {
        graphics::init();
        scene::init();
        ape::window::createdEvent.addCallback([&](Vec2i size){
            input::init();
        });

        detail::currentTime = hi_res_clock::now();

        world::setDefaultComponents<Transform>();
    }

    void update() {
        world::refresh();

        glfwPollEvents();
        input::ContextManager::pollInputStates();

        auto newTime = hi_res_clock::now();
        double elapsed = detail::getTimeFromPoints(detail::currentTime, newTime);
        detail::currentTime = newTime;

        detail::accumulator += elapsed;

        while(detail::accumulator >= detail::dt) {

            for(auto func : detail::simulationCode) {
                func(detail::dt);
            }

            for(auto& transform : world::getComponentList<Transform>()) {
                transform.move(transform.getVelocity() * detail::dt);
            }

            detail::accumulator -= detail::dt;
        }

        graphics::begin();
        scene::render();
        graphics::end();
    }

    void addSimulationCode(std::function<void(double dt)> function) {
        detail::simulationCode.push_back(function);
    }

    bool isRunning() {
        if(window::isOpen()) {
            return true;
        }

        window::destroy();
        return false;
    }
}
