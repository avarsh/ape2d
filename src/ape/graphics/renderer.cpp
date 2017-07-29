#include <ape/graphics/renderer.h>
#include <ape/core/transform.h>

namespace ape {
    Renderer::Renderer() {
        /**
         * The renderer has a few components:
         * - A vertex buffer object and an element
         *   buffer object - these are to render a single
         *   square.
         *
         * - A per-instance attribute buffer - this
         *   contains the data for each instance of the
         *   square, such as size and rotation. The
         *   glVertexAttribDivisor function is used so
         *   that all vertices in an instance use the
         *   same data.
         *
         * - A per-vertex attribute buffer - this contains
         *   the data for each vertex, such as texture
         *   co-ordinates and colour.
         *
         *   Alternatively, a Uniform Buffer Object or a
         *   Texture Buffer Object could be used to store
         *   this data. The shader code would refer to the
         *   gl_InstanceId and VertexId attributes to retrieve
         *   this data.
         */

        // Generate the buffers and array object
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        // Initialise buffers
        // The quad VBO
        glGenBuffers(1, &quadVBO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices),
                    (GLvoid*)quadVertices, GL_STATIC_DRAW);

        glGenBuffers(1, &quadEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
                    (GLvoid*)indices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

        // Position is at location 0
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                              4 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                              4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

        // Instance buffers
        glGenBuffers(1, &instVBO);
        glBindBuffer(GL_ARRAY_BUFFER, instVBO);

        glBufferData(GL_ARRAY_BUFFER, 65536, NULL, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat),
                              (GLvoid*)0);
        glVertexAttribDivisor(1, 1);
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    Renderer::~Renderer() {
        glDeleteBuffers(1, &quadVBO);
        glDeleteBuffers(1, &quadEBO);
        glDeleteBuffers(1, &instVBO);
    }

    void Renderer::begin() {
        rendered = 0;
    }

    void Renderer::draw(Sprite* sprite) {
        spriteList.push_back(sprite);
    }

    void Renderer::end(World& world) {
        for(Sprite* sprite : spriteList) {
            auto& transform = world.getComponent<Transform>(sprite->entity);
            Vec2f pos = transform.getPosition();

            //std::cout << pos.x << ", " << pos.y << std::endl;
            transforms.push_back(pos.x);
            transforms.push_back(pos.y);

            toRender++;
        }

        glBindBuffer(GL_ARRAY_BUFFER, instVBO);
        // The 2 is actually the amount of the data we're sending per instance
        glBufferSubData(GL_ARRAY_BUFFER, rendered * 2 * sizeof(float),
                        transforms.size() * sizeof(float),
                        &transforms[0]);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(vertexArray);

        glDrawElementsInstancedBaseInstance(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT,
                                0, toRender, rendered);
        glBindVertexArray(0);

        spriteList.clear();
        transforms.clear();
        rendered += toRender;
        toRender = 0;
    }
}
