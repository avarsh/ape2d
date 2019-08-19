#ifndef APE_DEBUG_H
#define APE_DEBUG_H

#include <iostream>

#ifndef NDEBUG
#define ASSERT_MSG(condition, message) \
    do { \
        if(!(condition)) {\
            std::cerr << "Assertion `" #condition "` failed in ! " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while(false)
#else
#define ASSERT_MSG(condition, message) do {} while(false)
#endif

#endif // APE_DEBUG_H