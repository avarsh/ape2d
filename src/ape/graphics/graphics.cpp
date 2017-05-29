#include <ape/graphics/graphics.h>
#include <ape/graphics/texture.h>
#include <iostream>

namespace ape {

    /*
     * TODO: we can only have one instance of this class currently since it
     * is managing the lifetime of GLFW. Maybe decouple the GLFW initalization
     * and destruction from this class and let it be managed by the core
     * engine? This could allow for some more interesting possibilities, e.g.
     * multiple "worlds" each with their own graphics module, such as a world
     * for the main menu, a world for the game, etc. We could also decouple
     * the world from the graphics module and require it to be passed in to
     * each function.
     */

    Graphics::Graphics(World& world) : world(world) {
        if(!glfwInit()) {
            std::cout << "GLFW failed to initalize!\n";
        }

        window.resizedEvent.addCallback([this](Vec2i newDims) {
            _setViewport(newDims);
        });
    }

    Graphics::~Graphics() {
        //batcher.deleteBuffers();

        window.destroy();
        glfwTerminate();
    }

    // Available window functions are described in detail here:
    // http://www.glfw.org/docs/latest/window_guide.html
    // They need to be exposed in the interface

    // TODO: allow fullscreen windows and borderless windowed
    void Graphics::init() {
        texturedShader.load("./data/shaders/textured.vert", "./data/shaders/textured.frag");
        texturedShader.use();

        // TODO: do this in the _setViewport function
        // We need to have a window created event to distinguish the inital
        // creation from subsequent resizes
        GLint projection = texturedShader.getUniformLocation("projection");
        glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    }

    void Graphics::draw() {
        texturedShader.use();

        int index = 0;
        glActiveTexture(GL_TEXTURE0);
        for(auto& texture : textureList) {
            texture.bind();
            glUniform1i(texturedShader.getUniformLocation("u_texture"), 0);

            // TODO: Presort the sprites...
            batcherList[index].draw(world);

            index++;
        }
    }

    Window& Graphics::getWindow() {
        return window;
    }

    void Graphics::_setViewport(Vec2i newDimensions) {
        glViewport(0, 0, newDimensions.x, newDimensions.y);
        projectionMatrix = glm::ortho(0.f, (float)newDimensions.x,
            (float)newDimensions.y, 0.0f, -1.0f, 1.0f);
    }

    int Graphics::addTexture(const Texture& texture) {
        int ID = textureList.size();

        textureList.push_back(texture);

        SpriteBatcher batcher;
        batcher.generateBuffers(ID);

        batcherList.push_back(batcher);

        return ID;
    }
}
