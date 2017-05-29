#ifndef VEC2_GLF_H
#define VEC2_GLF_H

#include <ape/utils/vector.h>
#include <glad/glad.h>

namespace ape {

    struct Vec2GLf : public Vec2<GLfloat> {
        Vec2GLf() {}
        Vec2GLf(GLfloat xValue, GLfloat yValue) :
            Vec2<GLfloat>(xValue, yValue) { }

        Vec2GLf& operator= (const Vec2<GLfloat>& v) {
            x = v.x;
            y = v.y;
            return *this;
        }
    };
}

#endif // VEC2_GLF_H
