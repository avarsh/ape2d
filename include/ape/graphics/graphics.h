#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <ape/graphics/window.h>
#include <ape/graphics/texture_store.h>
#include <ape/graphics/shader.h>
#include <ape/graphics/sprite.h>
#include <ape/graphics/color.h>
#include <ape/core/world.h>
#include <ape/graphics/renderer.h>

#include <ape/graphics/detail/graphics_detail.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <memory>
#include <set>

namespace ape {
    namespace graphics {
        void init ();

        void begin();
        void draw(Sprite* sprite);
        void end();
    };
}

#endif
