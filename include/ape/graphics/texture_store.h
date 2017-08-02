#ifndef MATERIAL_STORE_H
#define MATERIAL_STORE_H

#include <string>
#include <ape/graphics/texture.h>
#include <ape/core/event.h>
#include <memory>
#include <vector>

namespace ape {
    class TextureStore {
    public:
        int loadTexture(const std::string& source);
        void deleteTexture(int ID);
        std::shared_ptr<Texture> getTexture(int ID);

        Event<int> textureLoaded;
    private:
        std::vector<std::shared_ptr<Texture>> textureList;
    };
}

#endif // MATERIAL_STORE_H
