#include <ape/graphics/graphics.h>
#include <algorithm>

namespace ape {
    namespace graphics {

        void init() {
            glfwInit();
            glfwSetErrorCallback(detail::errorCallbackFunc);

            ape::window::createdEvent.addCallback([](Vec2i dims) {
                detail::instancedShader.load("data/shaders/textured.vert",
                                     "data/shaders/textured.frag");
                detail::setViewport(dims);
            });

            textureStore::textureLoaded.addCallback([](int ID) {
                detail::rendererStore.push_back(std::make_shared<Renderer>());
            });
        }

        void begin() {
            detail::spriteList.clear();
            detail::renderedTextures.clear();
        }

        void draw(Sprite* sprite) {
            detail::spriteList.push_back(sprite);
        }

        void end() {
            if(detail::spriteList.size() > 0) {
                detail::instancedShader.use();

                // Set the active texture unit to 0
                int loc = detail::instancedShader.getUniformLocation("tex");
                glUniform1i(loc, 0);
                glActiveTexture(GL_TEXTURE0);

                for(int i = 0; i < detail::spriteList.size(); i++) {
                    auto sprite     = detail::spriteList[i];
                    int textureID   = sprite->getTextureID();
                    auto texture    = textureStore::getTexture(textureID);
                    auto renderer   = detail::rendererStore[textureID];

                    if(detail::renderedTextures.find(textureID) == detail::renderedTextures.end()) {
                        // We haven't rendered this texture before on this frame
                        // so initialise the associated renderer
                        renderer->begin();
                        detail::renderedTextures.insert(textureID);
                    }

                    // Draw the sprite
                    renderer->draw(sprite);

                    // We want to flush the contents of the renderer to the GPU
                    // either if this is the last sprite or if the next sprite
                    // uses a different texture
                    bool last = (i == detail::spriteList.size() - 1);

                    if((last) || (!last && detail::spriteList[i + 1]->getTextureID() != textureID)) {
                        //texture->bind();
                        renderer->end(detail::instancedShader, *texture);
                    }
                }
            }
        }
    }
}
