#include <ape/input/detail/input_detail.h>

namespace ape::input::detail {

    void init() { }

    void handle(SDL_Event& event) {
        InputEventInfo eventInfo;

        switch(event.type) {
            case SDL_KEYDOWN:
                eventInfo.inputType = InputType::ACTION;
                eventInfo.eventType = EventType::KEY_DOWN;
                eventInfo.info.keyCode = (KeyCode)event.key.keysym.sym;
                eventQueue.push(eventInfo);
                break;
            case SDL_KEYUP:
                eventInfo.inputType = InputType::ACTION;
                eventInfo.eventType = EventType::KEY_UP;
                eventInfo.info.keyCode = (KeyCode)event.key.keysym.sym;
                eventQueue.push(eventInfo);
                break; 
        };
    }

    std::queue<InputEventInfo> eventQueue;
}
