#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <ape/graphics/window.h>
#include <ape/graphics/material.h>
#include <ape/graphics/shader.h>
#include <ape/graphics/sprite.h>
#include <ape/graphics/color.h>
#include <ape/core/world.h>

#include <vector>
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

        void begin();
        void draw(Sprite* sprite);
        void end();

    private:
        Window window;
        World& world;

        static void _errorCallbackFunc(int errorCode, const char* description);
        void _onWindowCreation();

        Shader instancedShader;

        std::vector<Sprite*> spriteList;
        //std::set<GLuint> renderedMaterials;
        std::vector<GLuint> renderedMaterials; // TODO: Change to set
    };
}

#endif
