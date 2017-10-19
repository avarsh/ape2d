#include <ape/input/detail/input_detail.h>
#include <ape/input/context_manager.h>

#include <iostream>
#include <map>

namespace ape {
    namespace input {
        namespace detail {
            void keyCallbackFunc(GLFWwindow* window, int key, int scancode,
                                 int action, int mods) {
                if(action == GLFW_REPEAT) return;

                InputData data;
                std::map<int, EventType> eventConversionMap = {
                    {GLFW_PRESS, EventType::KEY_PRESS},
                    {GLFW_RELEASE, EventType::KEY_RELEASE}
                };

                data.eventType = (action == GLFW_PRESS) ?
                    EventType::KEY_PRESS : EventType::KEY_RELEASE;
                data.eventData = key;

                ContextManager::transmitInput(data);
            }
        }
    }
}
