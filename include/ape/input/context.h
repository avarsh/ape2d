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
            void addActionCallback(InputData inputData,
                std::function<void(InputData)> callback);
        private:
            friend class ContextManager;

            Context() {}

            int priority {-1};

            using DeviceMap = std::map<int, std::function<void(InputData)>>;
            DeviceMap keyboardMappings;
        };
    }
}

#endif // CONTEXT_H
