#include <ape/graphics/texture.h>
#include <ape/core/vec2.h>
#include <SOIL2.h>
#include <iostream>

namespace ape {
    Texture::Texture(GLuint textureID, Vec2i size) {
        this->textureID = textureID;
        this->textureSize = size;
    }

    void Texture::bind() {
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

    GLuint Texture::getTextureID() {
        return textureID;
    }

    Vec2i Texture::getSize() {
        return textureSize;
    }
}
