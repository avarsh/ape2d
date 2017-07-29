#include <ape/graphics/graphics.h>
#include <algorithm>

namespace ape {
    Graphics::Graphics(World& world) : world(world) {
        glfwInit();
        glfwSetErrorCallback(_errorCallbackFunc);

        window.createdEvent.addCallback([this](Vec2i dims) {
            this->_onWindowCreation();
        });
    }

    Graphics::~Graphics() {
        window.destroy();
    }

    Window& Graphics::getWindow() {
        return window;
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

            //Material* previousMat = spriteList[0]->getMaterial();
            /*Material* previousMaterial  = spriteList[0]->getMaterial();
            Material* material          = previousMat;
            Renderer& previousRenderer  = previousMat->getRenderer();
            Renderer& renderer          = previousRenderer;
            auto currentTextureID       = previousMat->getTextureID();
            //material->bind();

            //Renderer& renderer = material->getRenderer();*/

            // Set the active texture unit to 0
            int loc = instancedShader.getUniformLocation("tex");
            glUniform1i(loc, 0);
            glActiveTexture(GL_TEXTURE0);

            // NB. This is kind of hacky - it's basically because
            // if we have one sprite, then the for loop never runs so
            // we never initialise the renderer
            auto sprite = spriteList[0];
            sprite->getMaterial()->getRenderer().begin();
            renderedMaterials.push_back(sprite->getMaterial()->getTextureID());

            // TODO: Change to getMaterialID()
            for(int i = 0; i < (spriteList.size() - 1); i++) {
                auto sprite         = spriteList[i];
                Material* material  = sprite->getMaterial();
                auto currentMatID   = material->getTextureID();

                if(std::find(renderedMaterials.begin(),
                             renderedMaterials.end(),
                             currentMatID) == renderedMaterials.end()) {
                    // We haven't rendered this material before on this frame
                    material->getRenderer().begin();
                    renderedMaterials.push_back(currentMatID);
                }

                auto nextSprite = spriteList[i + 1];

                material->getRenderer().draw(sprite);

                if(nextSprite->getMaterial()->getTextureID() != currentMatID) {
                    // The next sprite has a different material, so flush this
                    // renderer to the GPU
                    material->bind(); // Set the texture
                    material->getRenderer().end(world); // Flush data
                }
            }

            // We need to render the last sprite
            auto last = spriteList.back();
            Material* lastMaterial = last->getMaterial();
            lastMaterial->getRenderer().draw(last);

            lastMaterial->bind();
            lastMaterial->getRenderer().end(world);

            /*for(auto sprite : spriteList) {
                material = sprite->getMaterial();
                renderer = material->getRenderer();

                if(material->getTextureID() != currentTextureID) {
                    // We have changed the material so bind the previous material
                    // and flush the previous renderer
                    previousMaterial->bind();
                    previousRenderer.end(world);

                    // Update the previous material and the current texture
                    previousMaterial = material;
                    previousRenderer = renderer;
                    currentTextureID = material->getTextureID();
                }

                if(renderedMaterials.find(currentTextureID) == renderedMaterials.end()) {
                    renderer.begin();
                    renderedMaterials.insert(currentTextureID);
                }

                renderer.draw(sprite);
            }

            previousMat->bind();
            previousRenderer.end(world);*/
        }
    }

    void Graphics::_errorCallbackFunc(int errorCode, const char* description) {
        std::cout << "\n[ERROR] [" << errorCode << "] [GLFW]\n";
        std::cout << "======================================\n";
        std::cout << description << "\n";
    }

    void Graphics::_onWindowCreation() {
        instancedShader.load("data/shaders/instancedv1.vert",
                             "data/shaders/instancedv1.frag");
    }
}
