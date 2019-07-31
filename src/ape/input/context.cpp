#include <ape/input/context.h>

namespace ape {
    namespace input {
        Context::Context(int priority) : priority(priority) {}

        /*void Context::addCallback(InputType inputType, const std::string& name, std::function<bool(void)> callback) {
            callbacks[name] = callback;
            
        } */

        bool Context::compare(Context& c1, Context& c2) {
            return c1.priority < c2.priority;
        }

        std::priority_queue<Context, std::vector<Context>, std::function<bool(Context&, Context&)>> contextChain(Context::compare);
    }
}