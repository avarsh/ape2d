#include <ape/file/persistent.h>
#include <fstream>
#include <iostream>

namespace ape {
    Persistent::Persistent(const std::string& path) 
        : path(path) {
        
    }

    void Persistent::load() {
        try {
            fileStream.open(path, std::ios::in);
            fileStream >> jsonObj;
            this->fromJson();
        } catch (const std::fstream::failure& err) {
            std::cout << "Error opening file: " << err.what << std::endl;
        }

        fileStream.close();
    }

    void Persistent::save() {
        try {
            fileStream.open(path, std::ios::out | std::ios::trunc);
            fileStream << jsonObj;
            this->toJson();
        } catch (const std::fstream::failure& err) {
            std::cout << "Error opening file: " << err.what << std::endl;
        }

        fileStream.close();
    }
}