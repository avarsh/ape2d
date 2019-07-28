#ifndef APE_INPUT_CONFIG_H
#define APE_INPUT_CONFIG_H

#include <ape/file/persistent.h>

namespace ape {
    namespace input {
        class Config : public Persistent {
            public:
                Config();

                void toJson();
                void fromJson();
            private:
                // Map from key value to function name
        };
    }
}

#endif 