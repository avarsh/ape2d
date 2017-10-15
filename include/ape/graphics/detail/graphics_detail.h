#ifndef GRAPHICS_DETAIL_H
#define GRAPHICS_DETAIL_H

#include <ape/graphics/shader.h>
#include <ape/graphics/renderer.h>
#include <vector>
#include <set>
#include <ape/core/vec2.h>
#include <ape/graphics/sprite.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ape {
    namespace graphics {
        namespace detail {
            void errorCallbackFunc(int errorCode, const char* description);
            void setViewport(Vec2i newDimensions);

            extern Shader instancedShader;
            extern std::vector<Sprite*> spriteList;
            extern std::set<int> renderedTextures;
            extern glm::mat4 projectionMatrix;
            extern std::vector<std::shared_ptr<Renderer>> rendererStore;
        }
    }
}

#endif // GRAPHICS_DETAIL_H
