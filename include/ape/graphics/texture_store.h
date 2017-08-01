#ifndef MATERIAL_STORE_H
#define MATERIAL_STORE_H

#include <string>
#include <ape/graphics/texture.h>
#include <ape/core/event.h>
#include <vector>

namespace ape {
    class TextureStore {
    public:
        static int loadTexture(const std::string& source);
        static void deleteTexture(int ID);
        static Texture& getTexture(int ID);

        static Event<int> textureLoaded;
    private:
        static std::vector<Texture> textureList;
    };
}

#endif // MATERIAL_STORE_H
