#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <string>
#include <ape/utils/vector.h>

namespace ape {

    class Texture {
    public:
        Texture();

        bool load(std::string path);

        GLuint getID();

        void bind();
    private:
        GLuint textureID;
        Vec2i dimensions;
    };
}

#endif // TEXTURE_H
