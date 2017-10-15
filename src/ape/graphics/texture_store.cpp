#include <ape/graphics/texture_store.h>
#include <iostream>
#include <cassert>


namespace ape {
    namespace textureStore {
        Event<int> textureLoaded;

        int loadTexture(const std::string& source) {
            GLuint textureID;

            glActiveTexture(GL_TEXTURE0); // Set active texture to texture 0
            glGenTextures(1, &textureID); // Generate texture id

            glBindTexture(GL_TEXTURE_2D, textureID); // Bind the texture

            Vec2i textureSize;
            // Load image from path
            unsigned char* image = SOIL_load_image(source.c_str(), &textureSize.x,
                                                   &textureSize.y, 0, SOIL_LOAD_RGBA);

            // TODO: Move this into a logger class
            if(image == NULL) {
                std::cout << "\n[ERROR] [SOIL2]\n";
                std::cout << "===============\n";
                std::cout << "  Error when loading image from file: " << source << "\n";
                std::cout << "  " << SOIL_last_result() << "\n";

                return -1;
            }

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSize.x, textureSize.y, 0,
                         GL_RGBA, GL_UNSIGNED_BYTE, image);

            // TODO: Move this into a setSmooth() function
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glGenerateMipmap(GL_TEXTURE_2D);

            SOIL_free_image_data(image);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glBindTexture(GL_TEXTURE_2D, 0); // Unbind

            Vec2f fTextureSize(textureSize.x, textureSize.y);
            auto texture = std::make_shared<Texture>(textureID, fTextureSize);
            detail::textureList.push_back(texture);

            int ID = detail::textureList.size() - 1;
            textureLoaded.emit(ID);

            return ID;
        }

        std::shared_ptr<Texture> getTexture(int ID) {
            assert(ID >= 0 && ID < detail::textureList.size());

            return detail::textureList[ID];
        }

        void deleteTexture(int ID) {

        }
    }
}
