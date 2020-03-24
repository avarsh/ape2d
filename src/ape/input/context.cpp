#include <ape/input/context.h>
#include <ape/core/debug.h>

namespace ape {
    namespace input {

        context_t createContext(uint32_t priority) {
            context_t handle = detail::contextCounter++;
            detail::Context context;
            context.handle = handle;
            context.priority = priority;
            context.active = true;
            std::list<detail::Context>::iterator itemPosition = detail::contextChain.end();

            for (auto iter = detail::contextChain.begin(); iter != detail::contextChain.end(); iter++) {
                if (iter->priority < priority) {        
                    itemPosition = iter;
                    break;
                }
            }

            detail::contextMap[handle] = detail::contextChain.insert(itemPosition, context);
            return handle;
        }
        
        void addCallback(context_t context, InputEventInfo info, 
                         std::function<bool(InputEventInfo)>&& callback) {
            /* In theory, a context between 0 and the current counter value should
             * be valid and inserted into the map, but this is only true while
             * there is no removal functionality.
             */
            ASSERT_MSG(context >= 0 && context < detail::contextCounter, "Invalid context provided.");
            detail::contextMap[context]->inputMap[info] = std::move(callback);
        }

        void setActive(context_t context, bool setting) {
            ASSERT_MSG(context >= 0 && context < detail::contextCounter, "Invalid context provided.");
            detail::contextMap[context]->active = setting;
        }
    }
}
