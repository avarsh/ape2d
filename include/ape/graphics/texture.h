#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <string>

#include <ape/graphics/rect.h>

namespace ape {

    struct Texture {
        void bind();
        GLuint id;
        Vec2i size;
    };
}

#endif
