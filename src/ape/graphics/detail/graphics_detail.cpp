#include <ape/graphics/detail/graphics_detail.h>

namespace ape {
    namespace graphics {
        namespace detail {

            Shader instancedShader;
            std::vector<Sprite*> spriteList;
            std::set<int> renderedTextures;
            glm::mat4 projectionMatrix;
            std::vector<std::shared_ptr<Renderer>> rendererStore;

            void errorCallbackFunc(int errorCode, const char* description) {
                std::cout << "\n[ERROR] [" << errorCode << "] [GLFW]\n";
                std::cout << "======================================\n";
                std::cout << description << "\n";
            }

            void setViewport(FloatRect viewport, Vec2i displayArea) {

                glViewport(
                    viewport.origin.x * displayArea.x,
                    viewport.origin.y * displayArea.y,
                    viewport.size.x * displayArea.x,
                    viewport.size.y * displayArea.y
                );
            }

            void setProjection(FloatRect viewport, Vec2i displayArea,
                               Vec2f translation, Vec2f scale, float rotation) {
                projectionMatrix = glm::ortho(0.f,
                    (float)(viewport.size.x * displayArea.x),
                    (float)(viewport.size.y * displayArea.y),
                    0.0f, -1.0f, 1.0f);

                projectionMatrix = glm::scale(projectionMatrix,
                    glm::vec3(scale.x, scale.y, 0)); // Scales the image
                projectionMatrix = glm::translate(projectionMatrix,
                    glm::vec3(translation.x, translation.y, 0)); // Translates the image
                projectionMatrix = glm::rotate(projectionMatrix, rotation,
                    glm::vec3(1, 0, 0)); // Rotates the image

                // TODO: only set shader if it is not currently in use
                instancedShader.use();
                GLint projection = instancedShader.getUniformLocation("projection");
                glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
            }
        }
    }
}
