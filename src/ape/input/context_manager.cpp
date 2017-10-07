#include <ape/input/context_manager.h>

namespace ape {
     ContextPtr ContextManager::createContext() {
        auto contextPtr = std::make_shared<Context>();
        contextPtr->priority = contextCount;
        if(firstContext == nullptr) {
            firstContext = contextPtr;
            lastContext = contextPtr;
        } else {
            lastContext->nextContext = contextPtr;
        }

        contextCount++;
        return lastContext;
    }

    void ContextManager::setContextPriority(ContextPtr context) {

    }

    ContextPtr ContextManager::getFirstContext() {
        return firstContext;
    }

    void ContextManager::notify(int key, int action) {
        
    }
}
