#include <ape/graphics/mesh.h>

namespace ape {
    void Mesh::setTexture(const Texture& texture) {
        textureId = texture.id;
        // Set this to be the whole texture by default
        textureRect.position = Vec2i(0, 0);
        textureRect.size = textureSize = texture.size;

        vertices.clear();
        for(int i = 0; i < 4; i++) {
            vertices.push_back(Vertex());
        }

        vertices[0].texture.x = 0.f;
        vertices[0].texture.y = 0.f;

        vertices[1].texture.x = 0.f;
        vertices[1].texture.y = 1.f;

        vertices[2].texture.x = 1.f;
        vertices[2].texture.y = 1.f;

        vertices[3].texture.x = 1.f;
        vertices[3].texture.y = 0.f;
    }

    void Mesh::setTextureRect(int left, int top, int width, int height) {
        textureRect.position = Vec2i(left, top);
        textureRect.size = Vec2i(width, height);
    }

    Rect Mesh::getTextureRect() {
        return textureRect;
    }

    GLuint Mesh::getTextureId() const {
        return textureId;
    }

    std::vector<Vertex>& Mesh::getVertices() {
        return vertices;
    }

    VertexAttributes& Mesh::getAttributes() {
        return attributes;
    }

    Vec2f Mesh::getOrigin() {
        return origin;
    }

    void Mesh::setOrigin(Vec2f origin) {
        this->origin = origin;
    }
}
