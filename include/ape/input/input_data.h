#ifndef INPUT_DATA_H
#define INPUT_DATA_H

#include <ape/input/keys.h>

namespace ape {
    namespace input {
        enum class Device {
            KEYBOARD,
            MOUSE
        };

        enum class ActionType {
            KEY_PRESS = 1000,
            KEY_RELEASE = 2000,
            MOUSE_BUTTON_DOWN = 3000
        };

        enum class StateType {
            KEY_DOWN = 4000,
        };

        struct InputData {
            InputData() { }
            InputData(Device device) : device(device) { }
            Device device;
        };

        struct ActionData : public InputData {
            ActionData() { }

            ActionData(Device device, ActionType action, int data) :
                action(action), data(data), InputData(device) { }

            ActionType action;  // Press, release etc.
            int data;           // e.g. which key or mouse button

            int getID() {
                return static_cast<int>(action) + data;
            }
        };

        struct StateData : public InputData {
            StateData() { }

            StateData(Device device, StateType state, int data) :
                state(state), data(data), InputData(device) { }

            StateType state;  // Press, release etc.
            int data;           // e.g. which key or mouse button

            int getID() {
                return static_cast<int>(state) + data;
            }

            static StateType getStateFromID(int ID) {
                int stateCode = ID - (ID % 1000);
                return static_cast<StateType>(stateCode);
            }

            static int getDataFromID(int ID) {
                int stateData = ID % 1000;
                return stateData;
            }
        };
    }
}

#endif // INPUT_DATA_H
