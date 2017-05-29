#ifndef GRAPHICS_H
#define GRAPHICS_H



#include <ape/ecs/world.h>
#include <ape/utils/vector.h>

#include <ape/graphics/color.h>
#include <ape/graphics/shader.h>
#include <ape/graphics/sprite_batcher.h>
#include <ape/graphics/texture.h>
#include <ape/graphics/window.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

namespace ape {
    class Graphics {
    public:

        /**
         * Constructor initalizing the module with a reference to the
         * world it will display.
         */
        Graphics(World& world);

        /**
         * Destructor, terminates the window and the GLFW instance.
         */
        ~Graphics();

        void init();

        void draw();

        int addTexture(const Texture& texture);

        void createSprite();

        Window& getWindow();

    private:
        Vec2i dimensions;

        World& world;
        Window window;

        Shader texturedShader;
        SpriteBatcher batcher;

        std::vector<Texture> textureList;
        std::vector<SpriteBatcher> batcherList;

        glm::mat4 projectionMatrix;

        void _setViewport(Vec2i newDimensions);

    };
}

#endif // GRAPHICS_H
