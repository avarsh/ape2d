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
         *   A Texture Buffer Object - used to store
         *   vertex specific data such as texture coordinates.
         *   The shader code refers to the gl_InstanceId and
         *   VertexId attributes to retrieve this data.
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
                              2 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        // Instance buffers
        glGenBuffers(1, &instVBO);
        glBindBuffer(GL_ARRAY_BUFFER, instVBO);
        glBufferData(GL_ARRAY_BUFFER, 65536, NULL, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                              4 * sizeof(GLfloat), (GLvoid*)0);
        glVertexAttribDivisor(1, 1);
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE,
                              4 * sizeof(GLfloat),
                              (GLvoid*)(2 * sizeof(GLfloat)));
        glVertexAttribDivisor(3, 1);
        glEnableVertexAttribArray(3);

        // Vertex buffer
        GLfloat uvArray[] = {
            0.0f, 0.0f,
            0.0f, 1.f,
            1.f, 1.f,
            1.f, 0.0f
        };

        glGenBuffers(1, &vertTBO);
        glBindBuffer(GL_TEXTURE_BUFFER, vertTBO);
        glBufferData(GL_TEXTURE_BUFFER, 65536, NULL, GL_STATIC_DRAW);

        glActiveTexture(GL_TEXTURE0 + 1);
        glGenTextures(1, &vertTexture);
        glBindTexture(GL_TEXTURE_BUFFER, vertTexture);
        glTexBuffer(GL_TEXTURE_BUFFER, GL_RG32F, vertTBO);

        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_TEXTURE_BUFFER, 0);
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

    void Renderer::end(World& world, Shader& shader, Texture& texture) {
        int i = 1;
        for(Sprite* sprite : spriteList) {
            auto& transform = world.getComponent<Transform>(sprite->entity);
            Vec2f pos = transform.getPosition();
            Vec2f size = sprite->getSize();

            transforms.push_back(pos.x);
            transforms.push_back(pos.y);
            transforms.push_back(size.x);
            transforms.push_back(size.y);

            FloatRect normalized = sprite->getNormalizedSubRect();

            GLfloat uvArray[] = {
                // top left
                normalized.origin.x,
                normalized.origin.y,
                // bottom left
                normalized.origin.x,
                normalized.origin.y + normalized.size.y,
                // bottom right
                normalized.origin.x + normalized.size.x,
                normalized.origin.y + normalized.size.y,
                // top right
                normalized.origin.x + normalized.size.x,
                normalized.origin.y
            };

            uv.insert(uv.end(), uvArray, std::end(uvArray));

            toRender++;
            i++;
        }

        glBindBuffer(GL_ARRAY_BUFFER, instVBO);
        glBufferSubData(GL_ARRAY_BUFFER, rendered * 4 * sizeof(float),
                        transforms.size() * sizeof(float),
                        &transforms[0]);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_TEXTURE_BUFFER, vertTBO);
        glBufferSubData(GL_TEXTURE_BUFFER, rendered * 8 * sizeof(GLfloat),
                        uv.size() * sizeof(GLfloat),
                        &uv[0]);
        glBindBuffer(GL_TEXTURE_BUFFER, 0);

        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_BUFFER, vertTexture);
        glTexBuffer(GL_TEXTURE_BUFFER, GL_RG32F, vertTBO);

        glActiveTexture(GL_TEXTURE0);
        texture.bind();

        shader.setUniformInt("tex", 0);
        shader.setUniformInt("textureCoordinates", 1);

        glBindVertexArray(vertexArray);
        glDrawElementsInstancedBaseInstance(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT,
                                0, toRender, rendered);
        glBindVertexArray(0);

        spriteList.clear();
        transforms.clear();
        uv.clear();
        rendered += toRender;
        toRender = 0;
    }
}
