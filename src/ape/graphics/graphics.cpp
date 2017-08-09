#include <ape/graphics/graphics.h>
#include <algorithm>

namespace ape {
    Graphics::Graphics(World& world) : world(world) {
        glfwInit();
        glfwSetErrorCallback(_errorCallbackFunc);

        window.createdEvent.addCallback([this](Vec2i dims) {
            instancedShader.load("data/shaders/textured.vert",
                                 "data/shaders/textured.frag");
            _setViewport(dims);
        });

        textureStore.textureLoaded.addCallback([this](int ID) {
            rendererStore.push_back(std::make_shared<Renderer>());
        });
    }

    Graphics::~Graphics() {
        window.destroy();
    }

    Window& Graphics::getWindow() {
        return window;
    }

    TextureStore& Graphics::getTextureStore() {
        return textureStore;
    }

    void Graphics::begin() {
        spriteList.clear();
        renderedTextures.clear();
    }

    void Graphics::draw(Sprite* sprite) {
        spriteList.push_back(sprite);
    }

    void Graphics::end() {
        if(spriteList.size() > 0) {
            instancedShader.use();

            // Set the active texture unit to 0
            int loc = instancedShader.getUniformLocation("tex");
            glUniform1i(loc, 0);
            glActiveTexture(GL_TEXTURE0);

            for(int i = 0; i < spriteList.size(); i++) {
                auto sprite     = spriteList[i];
                int textureID   = sprite->getTextureID();
                auto texture    = textureStore.getTexture(textureID);
                auto renderer   = rendererStore[textureID];

                if(renderedTextures.find(textureID) == renderedTextures.end()) {
                    // We haven't rendered this texture before on this frame
                    // so initialise the associated renderer
                    renderer->begin();
                    renderedTextures.insert(textureID);
                }

                // Draw the sprite
                renderer->draw(sprite);

                // We want to flush the contents of the renderer to the GPU
                // either if this is the last sprite or if the next sprite
                // uses a different texture
                bool last = (i == spriteList.size() - 1);

                if((last) || (!last && spriteList[i + 1]->getTextureID() != textureID)) {
                    //texture->bind();
                    renderer->end(world, instancedShader, *texture);
                }
            }
        }
    }

    void Graphics::_errorCallbackFunc(int errorCode, const char* description) {
        std::cout << "\n[ERROR] [" << errorCode << "] [GLFW]\n";
        std::cout << "======================================\n";
        std::cout << description << "\n";
    }

    void Graphics::_setViewport(Vec2i newDimensions) {
        glViewport(0, 0, newDimensions.x, newDimensions.y);
        projectionMatrix = glm::ortho(0.f, (float)newDimensions.x,
            (float)newDimensions.y, 0.0f, -1.0f, 1.0f);

        // TODO: only set shader if it is not currently in use
        instancedShader.use();
        GLint projection = instancedShader.getUniformLocation("projection");
        glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    }
}
