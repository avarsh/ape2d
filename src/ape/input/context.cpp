#include <ape/input/context.h>
#include <iostream>

namespace ape {
    namespace input {
        void Context::addActionCallback(InputData inputData,
            std::function<void(InputData)> callback) {
            // Add a callback function to be executed when an action
            // such as a mouse click or a key press occurs
            if(inputData.device == Device::KEYBOARD) {
                keyboardMappings[inputData.getID()] = callback;
            }
        }
    }
}
