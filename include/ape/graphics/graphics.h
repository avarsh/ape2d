#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <map>
#include <stack>

#include <ape/core/world.h>
#include <ape/core/vec2.h>

#include <ape/graphics/color.h>
#include <ape/graphics/shader.h>
#include <ape/graphics/window.h>
#include <ape/graphics/vertex_attributes.h>
#include <ape/graphics/batch_renderer.h>
#include <ape/graphics/buffer.h>
#include <ape/graphics/texture.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SOIL2.h>

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

        // Disable copying
        Graphics(const Graphics& other) = delete;
        void operator=(const Window &other) = delete;

        /**
         * Retrieves the main window.
         * @return A reference to the window instance.
         */
        Window& getWindow();

        /**
         * Clears the window to a specified color, and prepares for drawing.
         * @param color The color to clear the window to.
         */
        void clear(Color color);

        /**
         * Draws an entity.
         * @param entity The entity to draw.
         */
        void draw(entity_t entity);

        /**
         * Displays the window, swapping buffers and rendering all meshes.
         */
        void display();

        /**
         * Loads a texture into memory.
         * @param  source The path to the texture file.
         * @return        A boolean indicating whether
         */
        Texture& loadTexture(const std::string& source);
    private:
        void _setViewport(Vec2i newDimensions);

        World& world;
        Window window;
        Shader texturedShader;
        glm::mat4 projectionMatrix;
        std::map<GLuint, Texture> textureMap;
        std::map<GLuint, BatchRenderer> rendererMap;

        std::vector<Mesh> meshDrawList;

        int maxSize {65536};
    };
}

#endif // GRAPHICS_H
