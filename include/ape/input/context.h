#ifndef CONTEXT_H
#define CONTEXT_H

#include <memory>
#include <ape/input/input_data.h>
#include <functional>
#include <map>

namespace ape {
    namespace input {
        class Context {
        public:
            void addActionCallback(ActionData actionData,
                std::function<void()> callback);
            void addStateCallback(StateData stateData,
                std::function<void()> callback);
        private:
            friend class ContextManager;

            Context() {}

            int priority {-1};

            using DeviceMap = std::map<int, std::function<void()>>;
            DeviceMap keyboardMappings;
            DeviceMap keyboardStates;

            void pollStates();
        };
    }
}

#endif // CONTEXT_H
