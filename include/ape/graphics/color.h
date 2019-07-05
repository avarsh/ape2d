#ifndef APE_COLOR_H
#define APE_COLOR_H

namespace ape {

    /**
     * A simple class which takes in integer values (ranging from 0 to 255) for
     * a colour and stores them in a normalized format (between 0 and 1). Only
     * supports opaque colours.
     */

    // This may not be the best option for storing the colours; maybe have
    // functions to get the actual colour and the normalized colour and store
    // both?
    struct Color {
        Color() { }

        Color(int red, int green, int blue) {
            this->red = red * divisor;
            this->green = green * divisor;
            this->blue = blue * divisor;
        }

        float red {1.f};
        float green {1.f};
        float blue {1.f};

    private:
        float divisor {1.f / 255.f};
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
