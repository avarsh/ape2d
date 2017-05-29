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
    }

    Graphics::~Graphics() {
        //batcher.deleteBuffers();

        if(window != nullptr) {
            glfwDestroyWindow(window);
        }

        glfwTerminate();
    }

    // Available window functions are described in detail here:
    // http://www.glfw.org/docs/latest/window_guide.html
    // They need to be exposed in the interface

    // TODO: allow fullscreen windows and borderless windowed
    void Graphics::createWindow(int width, int height, std::string title) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        dimensions = Vec2i(width, height);

        // Create the window
        window = glfwCreateWindow(dimensions.x, dimensions.y, title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(window);
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        glfwSwapInterval(0); // Turn off vsync by default

        // Set the viewport to be the same size as the window initially
        int viewWidth, viewHeight;
        glfwGetFramebufferSize(window, &viewWidth, &viewHeight);
        _setViewport(Vec2i(viewWidth, viewHeight));

        texturedShader.load("./data/shaders/textured.vert", "./data/shaders/textured.frag");
        texturedShader.use();

        GLint projection = glGetUniformLocation(texturedShader.getProgram(), "projection");
        glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    }

    // TODO: capture an attempt at the window closing in an event, by using
    // glfwSetWindowCloseCallback
    bool Graphics::windowIsOpen() {
        return !glfwWindowShouldClose(window);
    }

    void Graphics::clearWindow(Color color) {
        glClearColor(color.red, color.green, color.blue, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Graphics::displayWindow() {
        texturedShader.use();

        int index = 0;
        for(auto& texture : textureList) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture.getID());
            glUniform1i(glGetUniformLocation(texturedShader.getProgram(), "u_texture"), 0);

            // TODO: Presort the sprites...
            batcherList[index].draw(world);

            index++;
        }

        glfwSwapBuffers(window);
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
