#include <ape/input/input_info.h>

namespace ape::input {
    InputEventInfo::InputEventInfo(const InputEventInfo& other)  {
        inputType = other.inputType;
        eventType = other.eventType;
        info.raw = other.info.raw;
    }

    InputEventInfo InputEventInfo::keyDown(KeyCode key) {
        InputEventInfo info;
        info.inputType = InputType::ACTION;
        info.eventType = EventType::KEY_DOWN;
        info.info.keyCode = key;
        return info;
    }
}