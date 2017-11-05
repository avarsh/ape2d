#include <ape/scene/camera.h>

namespace ape {
    namespace scene {
        entity_t defaultCamera = ENTITY_INVALID;
    }

    void Camera::setViewport(FloatRect viewport) {
        this->viewport = viewport;
    }

    FloatRect Camera::getViewport() {
        return viewport;
    }
}
