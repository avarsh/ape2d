#include <ape/graphics/texture.h>
#include <SOIL2.h>

namespace ape {
    void Texture::bind() {
        glBindTexture(GL_TEXTURE_2D, id);
    }
}
