#include <ape/graphics/texture_store.h>
#include <SOIL2.h>
#include <iostream>
#include <cassert>

namespace ape {

    int TextureStore::loadTexture(const std::string& source) {
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
        textureList.push_back(texture);

        int ID = textureList.size() - 1;
        textureLoaded.emit(ID);

        return ID;
    }

    std::shared_ptr<Texture> TextureStore::getTexture(int ID) {
        assert(ID >= 0 && ID < textureList.size());

        return textureList[ID];
    }

    void TextureStore::deleteTexture(int ID) {

    }
}
