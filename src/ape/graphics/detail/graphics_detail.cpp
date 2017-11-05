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
                glViewport(viewport.origin.x, viewport.origin.y,
                    viewport.size.x * displayArea.x, viewport.size.y * displayArea.y);
                projectionMatrix = glm::ortho(0.f, (float)(viewport.size.x * displayArea.x),
                    (float)(viewport.size.y * displayArea.y), 0.0f, -1.0f, 1.0f);

                // TODO: only set shader if it is not currently in use
                instancedShader.use();
                GLint projection = instancedShader.getUniformLocation("projection");
                glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
            }
        }
    }
}
