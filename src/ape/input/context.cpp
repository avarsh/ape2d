#include <ape/input/context.h>
#include <ape/core/debug.h>

namespace ape {
    namespace input {

        context_t createContext(uint32_t priority) {
            context_t handle = detail::contextCounter++;

            for (auto iter = detail::contextChain.begin(); iter != detail::contextChain.end(); iter++) {
                if (iter->priority < priority) {
                    detail::Context context;
                    context.handle = handle;
                    context.priority = priority;
                    context.active = true;
                    auto itemIter = detail::contextChain.insert(iter, context);
                    detail::contextMap[handle] = itemIter;
                    break;
                }
            }

            return handle;
        }
        
        void addCallback(context_t context, InputEventInfo info, 
                         std::function<bool(InputEventInfo)>&& callback) {
            /* In theory, a context between 0 and the current counter value should
             * be valid and inserted into the map, but this is only true while
             * there is no removal functionality.
             */
            ASSERT_MSG(context >= 0 && context < detail::contextCounter, "Invalid context provided.");
            detail::contextMap[context]->inputMap.insert({info, std::move(callback)});
        }

        void setActive(context_t context, bool setting) {
            ASSERT_MSG(context >= 0 && context < detail::contextCounter, "Invalid context provided.");
            detail::contextMap[context]->active = setting;
        }
    }
}
