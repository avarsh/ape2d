#include <ape/graphics/material.h>
#include <ape/core/vec2.h>
#include <SOIL2.h>
#include <iostream>

namespace ape {
    void Material::bind() {
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

    GLuint Material::getTextureID() {
        return textureID;
    }

    bool Material::loadTexture(const std::string& source) {
        glActiveTexture(GL_TEXTURE0); // Set active texture to texture 0
        glGenTextures(1, &textureID); // Generate texture id

        bind(); // Bind the texture

        // Load image from path
        Vec2i size;
        unsigned char* image = SOIL_load_image(source.c_str(), &size.x, &size.y,
                                               0, SOIL_LOAD_RGBA);

        // TODO: Move this into a logger class
        if(image == NULL) {
            std::cout << "\n[ERROR] [SOIL2]\n";
            std::cout << "===============\n";
            std::cout << "  Error when loading image from file: " << source << "\n";
            std::cout << "  " << SOIL_last_result() << "\n";

            return false;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, image);

        // TODO: Move this into a setSmooth() function
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glGenerateMipmap(GL_TEXTURE_2D);

        SOIL_free_image_data(image);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBindTexture(GL_TEXTURE_2D, 0); // Unbind

        return true;
    }

    Renderer& Material::getRenderer() {
        return renderer;
    }
}
