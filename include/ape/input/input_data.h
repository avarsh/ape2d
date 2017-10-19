#ifndef INPUT_DATA_H
#define INPUT_DATA_H

namespace ape {
    namespace input {
        enum class Device {
            KEYBOARD,
            MOUSE
        };

        enum class EventType {
            KEY_PRESS = 1000,
            KEY_RELEASE = 2000,
            MOUSE_BUTTON_DOWN = 3000
        };

        enum Keys {
            // Use GLFW keys for now
        };

        struct InputData {
            InputData() { }

            InputData(Device device, EventType eventType, int eventData) :
                eventType(eventType), eventData(eventData), device(device) {
            }

            Device device; // Keyboard or mouse signal
            EventType eventType; // Press, release etc.
            int eventData; // e.g. which key or mouse button

            bool operator==(const InputData& comparisonData) {
                if((comparisonData.eventType == this->eventType) &&
                   (comparisonData.eventData == this->eventData)) {
                       return true;
                }

                return false;
            }

            int getID() {
                return static_cast<int>(eventType) + eventData;
            }
        };
    }
}

#endif // INPUT_DATA_H
