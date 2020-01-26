#include <ape/input/detail/context_detail.h>

namespace ape::input::detail {
    context_t contextCounter = 0;
    std::list<Context> contextChain;
    std::unordered_map<context_t, std::list<Context>::iterator> contextMap;
}
