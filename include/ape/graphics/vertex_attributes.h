#ifndef VERTEX_ATTRIBUTES_H
#define VERTEX_ATTRIBUTES_H

namespace ape {
    enum VertexAttributes {
        VERTEX_POSITION = 1,
        VERTEX_COLOR    = 1 << 1,
        VERTEX_TEXTURE  = 1 << 2
    };

    struct AttributeSizes {
        static int Position;
        static int Color;
        static int Texture;
    };

    enum AttributeLocations {
        LOCATION_POSITION = 0,
        LOCATION_COLOR    = 1,
        LOCATION_TEXTURE  = 2
    };

    static int getMeshDataSize(int attributes) {
        // Vertices always have a postion and color
        int size = AttributeSizes::Position + AttributeSizes::Color;
        if((attributes&VERTEX_TEXTURE) == VERTEX_TEXTURE) {
            size += AttributeSizes::Texture;
        }

        return size;
    }
}

#endif // VERTEX_ATTRIBUTES_H
