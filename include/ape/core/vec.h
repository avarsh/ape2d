#ifndef APE_VEC_H
#define APE_VEC_H

namespace ape {

    template<typename T>
    struct Vec2 {
        T i;
        T j;
    };

    using Vec2i = Vec2<int>;
    using Vec2u = Vec2<unsigned int>;
    using Vec2f = Vec2<float>;

    template<typename T>
    Vec2<T> operator+(Vec2<T> u, Vec2<T> v) {
        return {
            .i = u.i + v.i,
            .j = u.j + v.j
        };
    }

    template<typename T>
    Vec2<T> operator-(Vec2<T> u, Vec2<T> v) {
        return {
            .i = u.i - v.i,
            .j = u.j - v.j
        };
    }

    template<typename T>
    T dot(Vec2<T> u, Vec2<T> v) {
        return u.i * v.i + u.j * v.j;
    }


    template<typename T>
    Vec2<T> operator*(T a, Vec2<T> v) {
        return {
            .i = a * v.i,
            .j = a * v.j
        };
    }

    template<typename T>
    Vec2<T> operator*(Vec2<T> v, T a) {
        return a * v;
    }

    template<typename T>
    Vec2<T> operator/(Vec2<T> v, T a) {
        return {
            .i = v.i / a,
            .j = v.j / a
        };
    }
}

#endif