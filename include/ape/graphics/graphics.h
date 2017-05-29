#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ape/ecs/world.h>
#include <ape/utils/vector.h>

#include <ape/graphics/color.h>
#include <ape/graphics/shader.h>
#include <ape/graphics/sprite_batcher.h>
#include <ape/graphics/texture.h>

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

        /**
         * Initializes the main window.
         * @param width  The width of the window.
         * @param height The height of the window.
         * @param title  The string which will be the title of the window.
         */
        void createWindow(int width, int height, std::string title);

        /**
         * Checks whether the window is still open.
         * @return A boolean value indicating if the window is open.
         */
        bool windowIsOpen();

        /**
         * Clears the window to a specified color.
         * @param color The color to clear the window to.
         */
        void clearWindow(Color color);

        /**
         * Displays the window, swapping buffers and rendering all meshes.
         */
        void displayWindow();

        int addTexture(const Texture& texture);
    private:
        GLFWwindow* window {nullptr};
        Vec2i dimensions;

        World& world;

        Shader texturedShader;
        SpriteBatcher batcher;

        std::vector<Texture> textureList;
        std::vector<SpriteBatcher> batcherList;

        glm::mat4 projectionMatrix;

        void _setViewport(Vec2i newDimensions);

    };
}

#endif // GRAPHICS_H
