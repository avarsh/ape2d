#ifndef CONTEXT_H
#define CONTEXT_H

#include <memory>

namespace ape {
    class Context {
    public:
        using ContextPtr = std::shared_ptr<Context>;

        ContextPtr getNextContext();
    private:
        //std::shared_ptr<Context> prevContext {nullptr};
        ContextPtr nextContext {nullptr};
        int priority {-1};

        friend class ContextManager;
    };
}

#endif // CONTEXT_H
