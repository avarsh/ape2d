#ifndef APE_PERSISTENT_H
#define APE_PERSISTENT_H

#include <string>
#include <deps/json.hpp>
#include <fstream>

using nlohmann::json;

namespace ape {

    /* TODO: Have the game folder as a constant configured
       on initialisation */

    class Persistent {
        public:
            Persistent(const std::string& path);

            void load();
            void save();

            virtual void toJson() = 0;
            virtual void fromJson() = 0;
        protected:
            std::string path;
            json jsonObj;
            std::fstream fileStream;
            
    };
}

#endif 