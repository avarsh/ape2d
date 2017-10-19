#include <ape/input/input_system.h>

namespace ape {
    namespace input {
        void init() {
            glfwSetKeyCallback(ape::window::detail::window, detail::keyCallbackFunc);
        }
    }
}
