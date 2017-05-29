#ifndef COLOR_H
#define COLOR_H

#include <glad/glad.h>

namespace ape {

    struct Color {
        Color() { }

        Color(int red, int green, int blue) {
            this->red = red * divisor;
            this->green = green * divisor;
            this->blue = blue * divisor;
        }

        GLfloat red {1.f};
        GLfloat green {1.f};
        GLfloat blue {1.f};

    private:
        GLfloat divisor {1.f / 255.f};
    };

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

#endif // COLOR_H
