#include <ape/graphics/graphics.h>
#include <algorithm>

namespace ape {
    namespace graphics {

        void init() {
            // Set the error callback to our own function.
            glfwSetErrorCallback(detail::errorCallbackFunc);
            glfwInit();

            // Functions to execute once the window has been created.
            ape::window::createdEvent.addCallback([](Vec2i dims) {
                // Load the shader files into the instanced shader.
                detail::instancedShader.load("data/shaders/textured.vert",
                                             "data/shaders/textured.frag");
                // Set the default viewport to be the size of the window.
                detail::setViewport(FloatRect(0, 0, dims.x, dims.y), dims);
            });

            // Every time a texture is loaded, we create an associated
            // renderer.
            textureStore::textureLoaded.addCallback([](int ID) {
                detail::rendererStore.push_back(std::make_shared<Renderer>());
            });
        }

        // Begin clears the sprite list and the list of rendered textures.
        void begin() {
            detail::spriteList.clear();
            detail::renderedTextures.clear();
        }

        // Draw doesn't actually draw, it simply pushes the sprite onto the
        // queue of items to be drawn.
        void draw(Sprite* sprite) {
            detail::spriteList.push_back(sprite);
        }

        // Here is where the drawing actually occurs.
        // It automatically batches sprites together to allow for faster instanced
        // drawing of sprites, however exactly how efficient it is depends on 
        // how well the user groups their textures together.
        void end() {
            // Check if we have any sprites to render
            if(detail::spriteList.size() > 0) {
                // Activate the instanced sprite shader -
                // in the future if polygon rendering was to be implemented
                // then you would set a different shader.
                // TODO: Would be a good idea to have a state manager to avoid
                // calling this unnecessarily
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

                    // Find is logarithmic for a set
                    if(detail::renderedTextures.find(textureID) == detail::renderedTextures.end()) {
                        // We haven't rendered this texture before on this frame
                        // so initialise the associated renderer
                        // Remember, all the begin function does is reset the rendered count to 0
                        renderer->begin();
                        // Insert is also logarithmic in a set
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
