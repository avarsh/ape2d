#ifndef TEXTURE_STORE_DETAIL_H
#define TEXTURE_STORE_DETAIL_H

#include <vector>
#include <memory>
#include <ape/graphics/texture.h>

namespace ape {
    namespace textureStore {
        namespace detail {
            // List of textures
            extern std::vector<std::shared_ptr<Texture>> textureList;
        }
    }
}

#endif // TEXTURE_STORE_DETAIL_H
