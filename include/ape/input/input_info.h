#ifndef INPUT_INFO_H
#define INPUT_INFO_H

#include <ape/input/key_codes.h>
#include <iostream>

// Note that as a result of this the 
// engine is restricted to 64 bit systems
#define HASH_SIZE 64
#define INPUT_T_POS 59
#define EVENT_T_POS 51

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
            bool consumed {false};

            union {
                KeyCode keyCode;
                MouseButton mouseButton;
                int32_t raw;
            } info;

            bool operator==(const InputEventInfo& other) const {
                return (inputType == other.inputType) &&
                       (eventType == other.eventType) &&
                       (info.raw  == other.info.raw);
            }
        };

        struct InputEventInfoHasher {
            std::size_t operator()(const InputEventInfo& info) const {
                /*
                    Here's how the hashing works. We return a 32 bit integer, e.g.
                    
                   [31]     ->   ->   ->  ->   ->   ->   [0]
                    1000 0000 0000 0000 0000 0000 0000 0000

                    - Bits 63 - 60 identify the input type.
                    - Bits 59 - 52 identifies the event type.
                    - Bits 51 - 0 represent the event information.
                */
            
                int64_t inputTypeId;
                int64_t val;
                if (info.inputType == InputType::ACTION) {
                    val = 1UL;
                } else if (info.inputType == InputType::STATE) {
                    val = 2UL;
                } else if (info.inputType == InputType::RANGE) {
                    val = 3UL;
                }

                inputTypeId = val << INPUT_T_POS;

                int64_t eventTypeId;
                if (info.eventType == EventType::KEY_DOWN) {
                    val = 1UL;
                } else if (info.eventType == EventType::KEY_UP) {
                    val = 2UL;
                } else if (info.eventType == EventType::KEY_PRESS) {
                    val = 3UL;
                } else if (info.eventType == EventType::MOUSE_DOWN) {
                     val = 4UL;
                } else if (info.eventType == EventType::MOUSE_UP) {
                    val = 5UL;
                }

                eventTypeId = val << EVENT_T_POS;

                std::size_t hash = (inputTypeId ^ eventTypeId) ^ info.info.raw;
                return hash;
            }
        };
    }
}

#endif 
