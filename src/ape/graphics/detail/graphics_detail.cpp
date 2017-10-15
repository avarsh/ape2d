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

            void setViewport(Vec2i newDimensions) {
                glViewport(0, 0, newDimensions.x, newDimensions.y);
                projectionMatrix = glm::ortho(0.f, (float)newDimensions.x,
                    (float)newDimensions.y, 0.0f, -1.0f, 1.0f);

                // TODO: only set shader if it is not currently in use
                instancedShader.use();
                GLint projection = instancedShader.getUniformLocation("projection");
                glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
            }
        }
    }
}
