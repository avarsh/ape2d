#ifndef VERTEX_H
#define VERTEX_H

#include <ape/utils/vector.h>

namespace ape {

    /**
     * A vertex is simply a container for a 
     * position and a struct which holds values
     * for a colour. Should also hold texture 
     * co-ordinates in the future.
     */

    struct Vertex {
        Vec2f position;
        
        struct {
            float red {0.0f};
            float green {0.0f};
            float blue {0.0f};
        } color;
    };
}

#endif // VERTEX_H

