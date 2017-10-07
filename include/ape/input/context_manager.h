#ifndef CONTEXT_MANAGER_H
#define CONTEXT_MANAGER_H

#include <ape/input/context.h>
#include <memory>

namespace ape {
    using ContextPtr = std::shared_ptr<Context>;

    class ContextManager {
    public:
        ContextPtr createContext();
        void setContextPriority(ContextPtr context);
        ContextPtr getFirstContext();

        void notify(int key, int action);
    private:
        ContextPtr firstContext {nullptr};
        ContextPtr lastContext {nullptr};
        int contextCount {0};
    };
}

#endif // CONTEXT_MANAGER_H
