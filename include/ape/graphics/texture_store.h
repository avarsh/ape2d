#ifndef TEXTURE_STORE_H
#define TEXTURE_STORE_H

#include <string>
#include <ape/graphics/texture.h>
#include <ape/core/event.h>
#include <ape/graphics/detail/texture_store_detail.h>
#include <SOIL2.h>
#include <memory>
#include <vector>

namespace ape {
    namespace textureStore {
        int loadTexture(const std::string& source);
        void deleteTexture(int ID);
        std::shared_ptr<Texture> getTexture(int ID);

        extern Event<int> textureLoaded;
    }
}

#endif // TEXTURE_STORE_H
