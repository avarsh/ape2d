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
            rendererStore.push_back(std::make_unique<Renderer>());
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
        renderedMaterials.clear();
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

            // NB. This is kind of hacky - it's basically because
            // if we have one sprite, then the for loop never runs so
            // we never initialise the renderer
            auto sprite = spriteList[0];
            int textureID = sprite->getTextureID();
            auto texture = textureStore.getTexture(textureID);
            texture->bind();
            rendererStore[textureID]->begin();
            renderedMaterials.push_back(textureID);

            for(int i = 0; i < (spriteList.size() - 1); i++) {
                auto sprite         = spriteList[i];
                auto currentTexID   = sprite->getTextureID();
                auto texture       = textureStore.getTexture(currentTexID);
                auto& renderer      = rendererStore[currentTexID];

                if(std::find(renderedMaterials.begin(),
                             renderedMaterials.end(),
                             currentTexID) == renderedMaterials.end()) {
                    // We haven't rendered this material before on this frame
                    renderer->begin();
                    renderedMaterials.push_back(currentTexID);
                }

                auto nextSprite = spriteList[i + 1];

                renderer->draw(sprite);

                if(nextSprite->getTextureID() != currentTexID) {
                    // The next sprite has a different material, so flush this
                    // renderer to the GPU
                    texture->bind(); // Set the texture
                    renderer->end(world); // Flush data
                }
            }

            // We need to render the last sprite
            auto last = spriteList.back();
            texture = textureStore.getTexture(last->getTextureID());
            auto& renderer = rendererStore[last->getTextureID()];
            renderer->draw(last);

            texture->bind();
            renderer->end(world);
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
