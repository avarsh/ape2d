#ifndef APE_CONTEXT_H
#define APE_CONTEXT_H

#include <unordered_map>
#include <string>
#include <functional>
#include <queue>

#include <ape/input/key_codes.h>
#include <ape/input/input_info.h>
#include <ape/file/persistent.h>

namespace ape {
    namespace input {
        /**
         * An input context allows binding various input events to callback
         * functions. Loads and saves bindings to a file.
         */
        class Context : public Persistent {
        public:
            /**
             * Creates a context with a priority and a file to save to.
             * @param priority The priority of the context within the game.
             * @param path The path to save and load data from/to.
             */
            Context(int priority, const std::string& path);

            /* TODO: Consider using move semantics to gain ownership of function */
            /**
             * Adds a callback function for an input event.
             * @param info The input event specification.
             * @param name The name of the associated function.
             * @param callback The callback function to be executed.
             */
            void addCallback(InputEventInfo info, const std::string& name, std::function<bool(InputEventInfo)> callback);

            /**
             * Maps a function name to a callback.
             * @param name The name of the function.
             * @param callback The callback function to be executed.
             */
            void addCallback(const std::string& name, std::function<bool(InputEventInfo)> callback);
            
            /**
             * Sets the context as active or inactive. When inactive, events will fall through the chain.
             * @param setting Whether the context is active or inactive.
             */
            void setActive(bool setting);

            /**
             * Retrieves whether the context is active.
             * @return Whether the context is active.
             */
            bool getActive();

            /**
             * Consumes an event and executes any callbacks if present.
             * @param info The input event specification.
             * @return True if the event should continue down the chain, false if it has been eaten.
             */
            bool consume(InputEventInfo info);

            /**
             * Compares two contexts to see which has greater priority.
             * @param c1 The first context.
             * @param c2 THe second context.
             * @return True if c1 has lower priority than c2, false otherwise.
             */
            static bool compare(Context& c1, Context& c2);
        private:
            std::unordered_map<std::string, std::function<bool(InputEventInfo)>> callbacks;
            std::unordered_map<InputEventInfo, std::string, InputEventInfoHasher, InputEventInfoEquality> keymaps;
            int priority;
            bool active;
            
        protected:
            void toJSON();
            void fromJSON();
        };

        extern std::priority_queue<Context, std::vector<Context>, std::function<bool(Context&, Context&)>> globalContextChain;
    }
}

#endif