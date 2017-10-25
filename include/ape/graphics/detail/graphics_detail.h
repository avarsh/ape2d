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
            // Function to display errors created by GLFW
            void errorCallbackFunc(int errorCode, const char* description);
            // Updates the view so it matches the new window dimensions
            void setViewport(Vec2i newDimensions);

            extern Shader instancedShader; // Default shader, renders sprites
            extern std::vector<Sprite*> spriteList; // List of sprites to render
            extern std::set<int> renderedTextures; // Textures rendered this frame
            extern glm::mat4 projectionMatrix; // The projection matrix passed to shader
            // List of renderers, which have a 1-to-1 relationship with textures
            extern std::vector<std::shared_ptr<Renderer>> rendererStore;
        }
    }
}

#endif // GRAPHICS_DETAIL_H
