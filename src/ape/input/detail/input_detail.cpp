#include <ape/input/detail/input_detail.h>
#include <ape/input/context_manager.h>

#include <iostream>
#include <map>

namespace ape {
    namespace input {
        namespace detail {
            void keyCallbackFunc(GLFWwindow* window, int key, int scancode,
                                 int action, int mods) {
                if(action == GLFW_REPEAT) return; // Not supporting this yet

                ActionData data;

                data.action = (action == GLFW_PRESS) ?
                    ActionType::KEY_PRESS : ActionType::KEY_RELEASE;
                data.data = key;

                ContextManager::transmitAction(data);
            }
        }
    }
}
