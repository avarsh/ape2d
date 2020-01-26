#include <ape/ape.h>


namespace ape {

    using hi_res_clock = std::chrono::high_resolution_clock;

    void init() {
        world::setDefaultComponents<Transform>();

        graphics::detail::init();
        scene::detail::init();
        window::windowCreated.addCallback([&](Vec2i size){
            /* TODO: Initialize input */
        });

        detail::currentTime = hi_res_clock::now();
        detail::running = true;
    }

    bool isRunning() {
        return detail::running;
    }

    void update() {
        world::refresh();
        SDL_Event event;

        auto newTime = hi_res_clock::now();
        double elapsed = detail::getTimeFromPoints(detail::currentTime, newTime);
        detail::currentTime = newTime;
        detail::accumulator += elapsed;

        while(SDL_PollEvent(&event) > 0) {
            switch(event.type) {
                case SDL_QUIT:
                    window::windowClosed.emit();
                    detail::running = false;
                    break;
                default:
                    input::detail::handle(event);
                    break;
            }
        }

        input::detail::dispatch();

        while (detail::accumulator >= detail::dt) {
            for (const auto& func : detail::simulationCode) {
                func(detail::dt);
            }

            for (auto& transform : Transform::getPool()) {
                Vec2f velocity;
                if (world::entityHasComponent<Node>(transform.getEntity())) {
                    velocity = world::getComponent<Node>(transform.getEntity()).getGlobalTransform().velocity;
                } else {
                    velocity = transform.velocity;
                }

                transform.position += transform.velocity * detail::dt;
            }

            detail::accumulator -= detail::dt;
        }

        window::clear();
        scene::detail::render();
        window::display();
    }

    void addSimulationCode(std::function<void(double dt)> function) {
        detail::simulationCode.push_back(function);
    }

    void destroy() {
        TextureStore::freeTextures();
        graphics::detail::destroy();
    }
}