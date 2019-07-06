#ifndef APE_COLOR_H
#define APE_COLOR_H

#include <cstdint>

namespace ape {

    /**
     * A simple class which takes in integer values (ranging from 0 to 255) for
     * a colour and stores them in a normalized format (between 0 and 1). Only
     * supports opaque colours.
     */
    struct Color {
        Color() { }

        Color(int red, int green, int blue, int alpha=255) : 
            red(red), green(green), blue(blue), alpha(alpha) { }

        uint8_t red {255};
        uint8_t green {255};
        uint8_t blue {255};
        uint8_t alpha {255};
    };

    /**
     * A struct which holds predefined colours.
     */
    struct Colors {
        static Color Red;
        static Color White;
        static Color Blue;
        static Color Green;
        static Color Black;
        static Color Slate;
        static Color Sea;
        static Color Orange;
        static Color Sky;
    };
}

#endif
