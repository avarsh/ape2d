#ifndef VERTEX_ATTRIBUTES_H
#define VERTEX_ATTRIBUTES_H

#include <unordered_map>

namespace ape {

    // TODO: These class seem overkill, maybe just use something like
    // mesh.isTextured()?

    class VertexAttributes {
    public:
        void setAttributes(int attributes);
        int getAttributes();

        void setAttribute(int attribute, bool setting);

        bool has(int attribute);
        int getSize();
    private:
        int attributes;
    };

    struct VertexAttributeInfo {
        static int Position;
        static int Color;
        static int Texture;

        static int PositionSize;
        static int ColorSize;
        static int TextureSize;

        static int PositionLocation;
        static int ColorLocation;
        static int TextureLocation;

        static std::unordered_map<int, int> AttributeSizeMap;
    };
}

#endif // VERTEX_ATTRIBUTES_H
