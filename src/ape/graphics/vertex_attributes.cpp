#include <ape/graphics/vertex_attributes.h>
#include <iostream>

namespace ape {

    int VertexAttributeInfo::Position = 1;
    int VertexAttributeInfo::Color = 1 << 1;
    int VertexAttributeInfo::Texture = 1 << 2;

    int VertexAttributeInfo::PositionSize = 2;
    int VertexAttributeInfo::ColorSize = 3;
    int VertexAttributeInfo::TextureSize = 2;

    int VertexAttributeInfo::PositionLocation = 0;
    int VertexAttributeInfo::ColorLocation = 1;
    int VertexAttributeInfo::TextureLocation = 2;

    std::unordered_map<int, int> VertexAttributeInfo::AttributeSizeMap = {
        {VertexAttributeInfo::Position, VertexAttributeInfo::PositionSize},
        {VertexAttributeInfo::Color, VertexAttributeInfo::ColorSize},
        {VertexAttributeInfo::Texture, VertexAttributeInfo::TextureSize}
    };

    void VertexAttributes::setAttributes(int attributes) {
        this->attributes = attributes;
    }

    int VertexAttributes::getAttributes() {
        return this->attributes;
    }

    int VertexAttributes::getSize() {
        int size = 0;

        for(int i = (VertexAttributeInfo::AttributeSizeMap.size() - 1); i >= 0; i--) {
            int tempMask = attributes >> i;
            size += tempMask ? VertexAttributeInfo::AttributeSizeMap[1 << i] : 0;
        }

        // Only for testing - remove later...
        std::cout << size << std::endl;
        return size;
    }

    void VertexAttributes::setAttribute(int attribute, bool setting) {
        // I think this works...
        this->attributes = setting ?
            attributes | attribute :
            attributes & ~attribute;
    }

    bool VertexAttributes::has(int attribute) {
        return ((attributes&attribute) == attribute);
    }
}
