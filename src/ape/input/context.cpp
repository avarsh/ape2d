#include <ape/input/context.h>

namespace ape {
    std::shared_ptr<Context> Context::getNextContext() {
        return nextContext;
    }
}
