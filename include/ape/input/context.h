#ifndef CONTEXT_H
#define CONTEXT_H

#include <memory>
#include <functional>
#include <map>

namespace ape {
    enum Actions {
        KEY_PRESS,
        MOUSE_CLICK
    };

    enum States {
        KEY_HELD
    };

    enum Key {
        // Populate this
    };

    class Context {
    public:
        using ContextPtr = std::shared_ptr<Context>;

        ContextPtr getNextContext();

        void addAction(int actionType, int actionData,
                       std::function<void> callback);
        void addState(int state, int stateData, std::function<void> callback);
    private:
        //std::shared_ptr<Context> prevContext {nullptr};
        ContextPtr nextContext {nullptr};
        int priority {-1};

        std::map<int, std::function<void>> keyCallbacks;

        friend class ContextManager;
    };
}

#endif // CONTEXT_H
