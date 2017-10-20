#include <ape/input/context.h>
#include <iostream>
#include <ape/graphics/window.h>

namespace ape {
    namespace input {
        void Context::addActionCallback(ActionData actionData,
            std::function<void()> callback) {
            // Add a callback function to be executed when an action
            // such as a mouse click or a key press occurs
            if(actionData.device == Device::KEYBOARD) {
                keyboardMappings[actionData.getID()] = callback;
            }
        }

        void Context::addStateCallback(StateData stateData,
            std::function<void()> callback) {
            // Add a callback to be executed while in some input state
            if(stateData.device == Device::KEYBOARD) {
                keyboardStates[stateData.getID()] = callback;
            }
        }

        // Later on when implementing blocking, make this function take
        // a set (sorted by ID) showing which states were blocked by a higher
        // priority function
        void Context::pollStates() {
            for(auto const& iter : keyboardStates) {
                if(StateData::getStateFromID(iter.first) == StateType::KEY_DOWN) {
                    if(glfwGetKey(ape::window::detail::window,
                                  StateData::getDataFromID(iter.first)) == GLFW_PRESS) {
                        iter.second();
                    }
                }
            }
        }
    }
}
