#ifndef APE_INPUT_DETAIL_H
#define APE_INPUT_DETAIL_H

#include <SDL2/SDL.h>
#include <queue>
#include <ape/input/input_info.h>

namespace ape::input::detail {
    
    /* Sets up the input system. Currently has no functionality
     * but in future may be used to load bindings from a file.
     */
    void init();

    /* Builds a list of input events which can be dispatched 
     * down the context chain just once.
     */
    void handle(SDL_Event& event);

    /* Dispatches events through the context chain, allowing
     * callback functions to act.
     */
    void dispatch();

    extern std::queue<InputEventInfo> eventQueue;
}

#endif
