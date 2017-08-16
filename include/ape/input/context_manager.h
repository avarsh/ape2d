#ifndef CONTEXT_MANAGER_H
#define CONTEXT_MANAGER_H

#include <ape/input/context.h>
#include <memory>

namespace ape {
    class ContextManager {
    public:
        using ContextPtr = std::shared_ptr<Context>;

        ContextPtr createContext();
        void setContextPriority(ContextPtr context);
    private:
        ContextPtr firstContext {nullptr};
        ContextPtr lastContext {nullptr};
        int contextCount {0};
    };
}

#endif // CONTEXT_MANAGER_H
