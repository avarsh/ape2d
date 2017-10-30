#ifndef CAMERA_H
#define CAMERA_H

#include <ape/core/world.h>

namespace ape {
    class Camera : public Component<Camera> {
    public:
        Camera(entity_t entity) : Component<Camera>(entity) {}

    private:

    };

    namespace scene {
        extern entity_t defaultCamera;
    }
}

#endif // CAMERA_H
