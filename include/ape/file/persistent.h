#ifndef APE_PERSISTENT_H
#define APE_PERSISTENT_H

#include <string>
#include <deps/json.hpp>
#include <fstream>

using nlohmann::json;

namespace ape {

    /* TODO: Have the game folder as a constant configured
       on initialisation */

    /**
     * Class for persistent on-disk storage of game data in JSON format.
     */
    class Persistent {
        public:
            /**
             * Constructs class instance from path to file.
             * @param path String representing on disk path to file.
             */
            Persistent(const std::string& path);

            /**
             * Loads data from file.
             */
            void load();

            /**
             * Saves class data into file.
             */
            void save();
        protected:
            /**
             * Virtual method to allow derived classes to convert class data into JSON format.
             */
            virtual void toJson() = 0;

            /**
             * Virtual method to allow derived classes to parse data from JSON format.
             */
            virtual void fromJson() = 0;

            std::string path;
            json jsonObj;
            std::fstream fileStream;
            
    };
}

#endif 