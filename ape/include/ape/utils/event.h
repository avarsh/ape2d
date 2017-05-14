#ifndef EVENT_H
#define EVENT_H

#include <functional>
#include <vector>

namespace ape {

    /**
     * A simple base class for a generic event type.
     * An event supports any number of arguments. Callbacks
     * can be added to it, which will be executed upon 
     * emit
     */
    template <typename... Args>
    class Event {
        public:
            typedef std::function<void(Args...)> FuncType;

            void addCallback(FuncType function) {
                callbackFunctions.push_back(function);
            }

            void emit(Args... arguments) {
                for(auto func : callbackFunctions) {
                    func(arguments...);
                }
            }

        private:
            std::vector<FuncType> callbackFunctions;
    };
}

#endif // EVENT_H

