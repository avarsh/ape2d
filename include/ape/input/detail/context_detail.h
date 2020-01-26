#ifndef APE_CONTEXT_DETAIL_H
#define APE_CONTEXT_DETAIL_H

#include <list>
#include <unordered_map>
#include <functional>
#include <ape/input/input_info.h>

namespace ape {
    
    using context_t = uint32_t;

    namespace input {
        namespace detail {
           
            using input_map_t = std::unordered_map<
                                    InputEventInfo, 
                                    std::function<bool(InputEventInfo)>,
                                    InputEventInfoHasher, 
                                    InputEventInfoEquality
                                >;


            struct Context {
                uint32_t priority;
                context_t handle;
                input_map_t inputMap;
                bool active;
            };

            /* A counter to generate handles */
            extern context_t contextCounter;
            /* The list of contexts in order of priority */
            extern std::list<Context> contextChain;
            /* A mapping from a handle to the iterator at which we can
             * access the context within the list. Allows constant time
             * modification of the context, and iterators are not invalidated
             * in a list unless the item at that position is removed.
             */
            extern std::unordered_map<context_t, std::list<Context>::iterator> contextMap;
        }
    }
}

#endif 
