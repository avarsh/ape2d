#ifndef INPUT_DETAIL_H
#define INPUT_DETAIL_H

#include <ape/input/input_data.h>

#include <ape/graphics/graphics.h>
#include <ape/input/context_manager.h>

namespace ape {
    namespace input {
        namespace detail {
            void keyCallbackFunc(GLFWwindow* window, int key, int scancode,
                                 int action, int mods);
        }
    }
}

#endif // INPUT_DETAIL_H
