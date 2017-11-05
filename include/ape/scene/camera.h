#ifndef CAMERA_H
#define CAMERA_H

#include <ape/core/world.h>
#include <ape/core/rect.h>

namespace ape {
    class Camera : public Component<Camera> {
    public:
        Camera(entity_t entity) : Component<Camera>(entity) {}

        void setViewport(FloatRect viewport);
        FloatRect getViewport();
    private:
        FloatRect viewport { FloatRect(0, 0, 1, 1) };
    };

    namespace scene {
        extern entity_t defaultCamera;
    }
}

#endif // CAMERA_H
