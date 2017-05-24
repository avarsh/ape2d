#ifndef COLOR_H
#define COLOR_H

namespace ape {
    struct Color {
        Color() {}
        Color(GLfloat red, GLfloat green, GLfloat blue) :
            red(red), green(green), blue(blue) {

        }

        GLfloat red     {1.0f};
        GLfloat green   {1.0f};
        GLfloat blue    {1.0f};
    };
}

#endif
