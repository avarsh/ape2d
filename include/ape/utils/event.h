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

        /**
         * Allows subscribers to add a function to be executed
         * when the event is emitted.
         * @param function A std::function that matches the event's signature.
         */
        void addCallback(FuncType function) {
            callbackFunctions.push_back(function);
        }

        /**
         * Allows the event publisher to emit the event.
         * @param arguments All the arguments which match the event signature.
         */
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
