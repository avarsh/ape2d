#ifndef APE_EVENT_H
#define APE_EVENT_H

#include <functional>
#include <utility>
#include <cstdint>

namespace ape {
    using func_id_t = uint32_t;

    /**
     * A simple base class for a generic event type.
     * An event supports any number of arguments. Callbacks
     * can be added to it, which will be executed upon
     * emitting. Callbacks do not receive any priority.
     */
    template <typename... Args>
    class Event {
    public:
        using FuncType = std::function<void(Args...)>;

        /**
         * Allows subscribers to add a function to be executed
         * when the event is emitted.
         * @param function A std::function that matches the event's signature.
         * @return An identifier for the callback function.
         */
        func_id_t addCallback(FuncType function) {
            func_id_t id = idCounter++;
            callbackFunctions.push_back(std::make_pair(id, function));
            return id;
        }

        /**
         * Removes a callback function from the event, effectively 
         * unsubscribing from the event.
         * @param id The identifier for the callback function.
         */
        void removeCallback(func_id_t id) {
            for (int i = 0; i < callbackFunctions.size(); i++) {
                if (callbackFunctions[i].first == id) {
                    std::swap(callbackFunctions[i], callbackFunctions.back());
                    callbackFunctions.pop_back();
                    return; 
                }
            }
        }

        /**
         * Allows the event publisher to emit the event.
         * @param arguments All the arguments which match the event signature.
         */
        void emit(Args... arguments) {
            for(auto func : callbackFunctions) {
                func.second(arguments...);
            }
        }
    private:
        using FuncTypePair = std::pair<int, FuncType>;
        std::vector<FuncTypePair> callbackFunctions;
        static func_id_t idCounter;
    };

    template <typename... Args>
    func_id_t Event<Args...>::idCounter = 0;
}

#endif 
