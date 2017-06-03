#include <ape/graphics/graphics.h>
#include <stdexcept>
#include <iostream>
#include <algorithm>

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

        window.createdEvent.addCallback([this](Vec2i newDims) {
            texturedShader.load("./data/shaders/textured.vert", "./data/shaders/textured.frag");
            _setViewport(newDims);
        });

        window.resizedEvent.addCallback([this](Vec2i newDims) {
            _setViewport(newDims);
        });
    }

    Graphics::~Graphics() {
        window.destroy();
        glfwTerminate();
    }

    void Graphics::clear(Color color) {
        glClearColor(color.red, color.green, color.blue, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        meshDrawList.clear();

        for(auto& rendererPair : rendererMap) {
            rendererPair.second.begin();
        }
    }

    void Graphics::draw(entity_t entity) {
        meshDrawList.push_back(world.getComponent<Mesh>(entity));
    }

    void Graphics::display() {

        texturedShader.use();
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(texturedShader.getUniformLocation("u_texture"), 0);

        if(meshDrawList.size() > 0) {

            GLuint currentTextureId = meshDrawList[0].getTextureId();

            for(auto& mesh : meshDrawList) {
                if(mesh.getTextureId() != currentTextureId) {
                    textureMap[currentTextureId].bind();
                    rendererMap[currentTextureId].flush(world);

                    currentTextureId = mesh.getTextureId();
                }

                rendererMap[currentTextureId].addMesh(mesh);
            }

            textureMap[currentTextureId].bind();
            rendererMap[currentTextureId].flush(world);
        }

        glfwSwapBuffers(window.getWindow());
    }

    Window& Graphics::getWindow() {
        return window;
    }

    Texture& Graphics::loadTexture(const std::string& source) {
        GLuint texId;

        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &texId);
        glBindTexture(GL_TEXTURE_2D, texId);

        Vec2i size;

        unsigned char* image = SOIL_load_image(source.c_str(), &size.x, &size.y,
            0, SOIL_LOAD_RGBA);

        if(image == NULL) {
            throw std::runtime_error("Error occured when loading the texture at path " + source + ": " + std::string(SOIL_last_result()));
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

        SOIL_free_image_data(image);

        glEnable (GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBindTexture(GL_TEXTURE_2D, 0);

        textureMap[texId] = Texture();
        textureMap[texId].id = texId;
        textureMap[texId].size = size;

        rendererMap[texId] = BatchRenderer();
        rendererMap[texId].setTextureId(texId);

        return textureMap[texId];
    }

    void Graphics::_setViewport(Vec2i newDimensions) {
        glViewport(0, 0, newDimensions.x, newDimensions.y);
        projectionMatrix = glm::ortho(0.f, (float)newDimensions.x,
            (float)newDimensions.y, 0.0f, -1.0f, 1.0f);

        // TODO: only set shader if it is not currently in use
        texturedShader.use();
        GLint projection = texturedShader.getUniformLocation("projection");
        glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    }
}
