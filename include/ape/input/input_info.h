#ifndef INPUT_INFO_H
#define INPUT_INFO_H

#include <ape/input/key_codes.h>
#include <iostream>

namespace ape {
    namespace input {
        enum class InputType {
            ACTION,
            STATE,
            RANGE
        };

        enum MouseButton {
            BTN_LEFT,
            BTN_MIDDLE,
            BTN_RIGHT
        };

        enum class EventType {
            KEY_DOWN,
            KEY_UP,
            KEY_PRESS,
            MOUSE_DOWN,
            MOUSE_UP
        };

        struct InputEventInfo {
            InputType inputType;
            EventType eventType;

            union {
                KeyCode keyCode;
                MouseButton mouseButton;
                int32_t raw;
            } info;
        };

        struct InputEventInfoHasher {
            std::size_t operator()(const InputEventInfo& info) const {
                /*
                    Here's how the hashing works. We return a 32 bit integer, e.g.
                    
                   [31]     ->   ->   ->  ->   ->   ->   [0]
                    1000 0000 0000 0000 0000 0000 0000 0000

                    - Bits 31 - 28 identify the input type.
                    - Bits 27 - 20 identifies the event type.
                    - Bits 19 - 0 represent the event information.
                */
            
                int32_t inputTypeId;
                if (info.inputType == InputType::ACTION) {
                    inputTypeId = 1 << 28;
                } else if (info.inputType == InputType::STATE) {
                    inputTypeId = 2 << 28;
                } else if (info.inputType == InputType::RANGE) {
                    inputTypeId = 3 << 28;
                }

                int32_t eventTypeId;
                if (info.eventType == EventType::KEY_DOWN) {
                    inputTypeId = 1 << 20;
                } else if (info.eventType == EventType::KEY_UP) {
                    inputTypeId = 2 << 20;
                } else if (info.eventType == EventType::KEY_PRESS) {
                    inputTypeId = 3 << 20;
                } else if (info.eventType == EventType::MOUSE_DOWN) {
                    inputTypeId = 4 << 20;
                } else if (info.eventType == EventType::MOUSE_UP) {
                    inputTypeId = 5 << 20;
                }

                std::cout << "Input ID: " << inputTypeId << ", Event ID: " 
                    << eventTypeId << ", Info: " << info.info.raw << "\n";

                std::size_t hash = (inputTypeId ^ eventTypeId) ^ info.info.raw;
                std::cout << "Hash: " << hash << "\n";
                return hash;
            }
        };

        struct InputEventInfoEquality {
            std::size_t operator()(const InputEventInfo& info1, const InputEventInfo& info2) const {
                return (info1.inputType == info2.inputType) &&
                       (info1.eventType == info2.eventType) &&
                       (info1.info.raw == info2.info.raw);
            }
        };
    }
}

#endif 