#include <ape/ape.h>
#include <ape/detail/ape_detail.h>
#include <ape/graphics/graphics.h>

namespace ape {
    void init() {
        graphics::detail::init();
    }

    bool isRunning() {
        return detail::running;
    }

    void destroy() {
        graphics::detail::destroy();
    }
}