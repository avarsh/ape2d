#include <glad/glad.h>
#include <ape/ecs/component.h>
#include <ape/utils/vector.h>
#include <vector>

namespace ape {

    struct Vertex {
        Vertex() {}
        Vertex(GLfloat x, GLfloat y, GLfloat red, GLfloat green, GLfloat blue) {
            position.x = x;
            position.y = y;
            colors.red = red;
            colors.green = green;
            colors.blue = blue;
        }

        Vec2<GLfloat> position;

        struct {
            GLfloat red;
            GLfloat green;
            GLfloat blue;
        } colors;
    };

    struct Mesh : public ape::Component<Mesh> {
        int dataSize {5}; // Probably not needed

        std::vector<Vertex> vertices; // Change this to an array maybe?
        std::vector<GLushort> indices;

        int bufferIndex {-1}; // Will be used later when we have more than 1 buffer
    };
}
