#ifndef CONTEXT_MANAGER_H
#define CONTEXT_MANAGER_H

#include <ape/input/context.h>
#include <memory>
#include <list>

namespace ape {
    namespace input {
        class ContextManager {
        public:
            static Context& createContext(unsigned int priority = 0);
            static void transmitInput(InputData inputData);
        private:
            static std::list<Context> contextList;
        };
    }
}

#endif // CONTEXT_MANAGER_H
