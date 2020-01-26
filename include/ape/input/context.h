#ifndef APE_CONTEXT_H
#define APE_CONTEXT_H

#include <unordered_map>
#include <string>
#include <functional>

#include <ape/input/key_codes.h>
#include <ape/input/input_info.h>
#include <ape/file/persistent.h>
#include <ape/input/detail/context_detail.h>

namespace ape {
    namespace input {

        /* @brief Creates a context and returns a handle to it. 
         * @param priority The priority of the context.
         * @return         A handle to the context. 
         */
        context_t createContext(uint32_t priority);

        /* Adds a callback for an input event for a given context. 
         * @param context  The context to append to.
         * @param info     The information for the input event.
         * @param callback The callback to execute when the event fires.
         */
        void addCallback(context_t context, InputEventInfo info, std::function<bool(InputEventInfo)>&& callback);

        /* Sets the supplied context as active or inactive.
         * @param context The context to modify.
         * @param setting The new state of the context.
         */
        void setActive(context_t context, bool setting);
    }
}

#endif
