#ifndef MESH_H
#define MESH_H

#include <vector>

#include <ape/core/component.h>
#include <ape/graphics/vertex.h>
#include <ape/graphics/texture.h>
#include <ape/graphics/rect.h>
#include <ape/graphics/vertex_attributes.h>

namespace ape {

    class Mesh : public Component<Mesh> {
    public:
        void setTexture(const Texture& texture);
        void setTextureRect(int left, int top, int width, int height);

        GLuint getTextureId() const;
        Rect getTextureRect();

        Vec2f getTextureSize();

        std::vector<Vertex>& getVertices();
        //std::vector<GLushort>& getIndices();

        VertexAttributes& getAttributes();

        Vec2f getOrigin();
        void setOrigin(Vec2f origin);
    private:
        std::vector<Vertex> vertices;
        //std::vector<GLushort> indices;

        VertexAttributes attributes;

        GLuint textureId {0};
        Rect textureRect;

        Vec2i textureSize;

        Vec2f origin;
    };
}

#endif // MESH_H
