#include <ape/graphics/texture.h>
#include <SOIL2.h>

namespace ape {
    Texture::Texture() { }

    bool Texture::load(std::string path) {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        unsigned char* image = SOIL_load_image(path.c_str(), &dimensions.x,
            &dimensions.y, 0, SOIL_LOAD_RGBA);

        if(image == NULL) {
            return false;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dimensions.x, dimensions.y,
            0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

        SOIL_free_image_data(image);

        glBindTexture(GL_TEXTURE_2D, 0);

        return true;
    }

    GLuint Texture::getID() {
        return textureID;
    }

    void Texture::bind() {
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
}
