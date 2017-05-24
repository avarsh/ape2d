#include <glad/glad.h>
#include <ape/ecs/component.h>
#include <ape/utils/vector.h>
#include <ape/graphics/color.h>
#include <vector>

namespace ape {

    enum VertexMask {
        VM_POSITION = 1,
        VM_COLOR    = 1 << 1,
        VM_TEXTURE  = 1 << 2
    };

    struct Vertex {

        // Default constructor - does nothing
        Vertex() {}

        // Creates a vertex from a set of parameters
        Vertex(GLfloat x, GLfloat y, GLfloat red, GLfloat green, GLfloat blue) {
            position.x = x;
            position.y = y;
            color.red = red;
            color.green = green;
            color.blue = blue;
        }

        Vec2<GLfloat> position; // Position of the vertex
        Color color;            // RGB values for the color (alpha not supported yet)
        Vec2<GLfloat> texCoord; // Texture coordinates
    };

    struct Mesh : public ape::Component<Mesh> {
        int dataSize {5}; // Probably not needed

        std::vector<Vertex> vertices; // Change this to an array maybe?
        std::vector<GLushort> indices;

        int bufferIndex {-1}; // Will be used later when we have more than 1 buffer

        int mask { VM_POSITION | VM_COLOR }; // Defines what attributes are enabled
    };
}
