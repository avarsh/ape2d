#include <ape/input/context_manager.h>
#include <iterator>
#include <ape/graphics/graphics.h>
#include <iostream>

namespace ape {
    namespace input {

        std::list<Context> ContextManager::contextList;

        Context& ContextManager::createContext(unsigned int priority) {
            auto iter = contextList.begin();
            Context context;
            context.priority = priority;

            int pos = 0;

            // Insert the new context before the first context with a
            // lower priority
            if(contextList.empty()) {
                contextList.insert(iter, context);
            } else {
                bool inserted = false;
                while(iter != contextList.end()) {
                    if((*iter).priority < priority) {
                        contextList.insert(iter, context);
                        inserted = true;
                        break;
                    }

                    pos++;
                    std::advance(iter, 1);
                }

                if(!inserted) {
                    iter = contextList.end();
                    contextList.insert(iter, context);
                    pos = contextList.size() - 1;
                }
            }

            iter = contextList.begin();
            std::advance(iter, pos);
            return *(iter);
        }

        void ContextManager::transmitInput(InputData inputData) {
            auto iter = contextList.begin();

            while(iter != contextList.end()) {
                Context::DeviceMap& deviceMap = (*iter).keyboardMappings;

                auto mapping = (*iter).keyboardMappings.find(inputData.getID());
                if(mapping != (*iter).keyboardMappings.end()) {
                    mapping->second(inputData); // Execute the function
                }
                std::advance(iter, 1);
            }
        }
    }
}
