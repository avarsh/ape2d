#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <ape/graphics/window.h>
#include <ape/graphics/texture_store.h>
#include <ape/graphics/shader.h>
#include <ape/graphics/sprite.h>
#include <ape/graphics/color.h>
#include <ape/core/world.h>
#include <ape/graphics/renderer.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <memory>
#include <set>

namespace ape {
    class Graphics {
    public:
        Graphics(World& world);
        ~Graphics();

        /**
         * Get the window object associated with the graphics class
         * instance.
         * @return A reference to the window class instance.
         */
        Window& getWindow();

        TextureStore& getTextureStore();

        void begin();
        void draw(Sprite* sprite);
        void end();
    private:
        Window window;
        World& world;

        static void _errorCallbackFunc(int errorCode, const char* description);
        void _setViewport(Vec2i newDimensions);

        Shader instancedShader;

        std::vector<Sprite*> spriteList;
        //std::set<GLuint> renderedMaterials;
        std::vector<GLuint> renderedMaterials; // TODO: Change to set
        glm::mat4 projectionMatrix;

        std::vector<std::unique_ptr<Renderer>> rendererStore;

        TextureStore textureStore;
    };
}

#endif
