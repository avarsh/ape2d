#ifndef APE_CONTEXT_H
#define APE_CONTEXT_H

#include <unordered_map>
#include <string>
#include <functional>
#include <queue>

#include <ape/input/keycodes.h>

namespace ape {
    namespace input {
        enum class InputType {
            ACTION,
            STATE,
            RANGE
        };

        struct InputEventInfo {
            InputType inputType;
            union {
                KeyCode::Values keyCode;
                //MouseButton mouseButton;
            };
        };

        class Context {
        public:
            Context(int priority);

            /* TODO: Consider using move semantics to gain ownership of function */
            //void addCallback(InputEventInfo info, const std::string& name, std::function<bool(void)> callback);
            //bool hasBinding(InputEventInfo info);
            //void setActive(bool setting);
            //bool getActive();

            static bool compare(Context& c1, Context& c2);
        private:
            std::unordered_map<std::string, std::function<bool(void)>> callbacks;
            int priority;
        };

        extern std::priority_queue<Context, std::vector<Context>, std::function<bool(Context&, Context&)>> contextChain;
    }
}

#endif