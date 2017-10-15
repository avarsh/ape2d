#ifndef DEFINES_H
#define DEFINES_H

namespace ape {
    // Allows us to easily change the type of an entity, to accomodate
    // more or less entity IDs
    using entity_t = unsigned int;

    extern entity_t ENTITY_INVALID;
}

#endif // DEFINES_H
