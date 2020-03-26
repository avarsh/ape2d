#include <ape/input/detail/input_detail.h>
#include <ape/input/detail/context_detail.h>

namespace ape::input::detail {

    void init() { }

    void handle(SDL_Event& event) {
        InputEventInfo eventInfo;

        switch(event.type) {
            case SDL_KEYDOWN:
                eventInfo.inputType = InputType::ACTION;
                eventInfo.eventType = EventType::KEY_DOWN;
                eventInfo.info.keyCode = (KeyCode)event.key.keysym.sym;
                break;
            case SDL_KEYUP:
                eventInfo.inputType = InputType::ACTION;
                eventInfo.eventType = EventType::KEY_UP;
                eventInfo.info.keyCode = (KeyCode)event.key.keysym.sym;
                break; 
            default:
                return;
        };

        eventQueue.push(eventInfo);
    }

    void dispatch() {
        // We take each event in turn and propagate it through 
        // the chain of contexts.
        while (!eventQueue.empty()) {
            auto event = eventQueue.front();

            for (auto& context : contextChain) {
                if (context.active && context.inputMap.count(event) == 1) {
                    auto& response = context.inputMap[event];
                    bool consumed = response(event);
                    if (consumed) break;
                }
            }

            eventQueue.pop();
        }
    }

    std::queue<InputEventInfo> eventQueue;
}
