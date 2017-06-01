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

    /*
     * This is a prototype for a queue based event system
     * Similarly to how components work, each event holds a queue of
     * its own event instances. Events can be pushed directly to this queue.
     * However, to make sure events are polled in order, the event manager
     * class is used. The main idea is that the actual event queue just holds
     * the eventId, so a system can do something like:
     *
     *      void receiveEvent(int eventId) {
     *          if(eventId == InterestingEvent::Id) {
     *              InterestingEvent event = InterestingEvent::Queue.front();
     *              // Do interesting things
     *          }
     *      }
     *
     * Things which need to actually be thought about:
     *  -> What pattern to use - publisher/subscriber, and how to actually notify
     *     systems of events, and how systems can subscribe to events
     *  -> Encapsulating pushing the event on to the event's queue AND the event
     *     Id queue.
     *  -> The use case - I intended this for applications where no immediate
     *     response is required (i.e. the state of the world can change). One
     *     case could be polling input and window events.
     *
     * I'll get round to it but focusing on getting the graphics working right now.
     */

    /*
    template<class DerivedEvent>
    class QueuedEvent {
    public:
        static int Id;
        static std::queue<DerivedEvent> Queue;
    };

    class EventManager {
    public:
        void pushEvent(int eventId);
    private:
        std::queue<int> eventQueue;
    };
    */
}

#endif // EVENT_H
