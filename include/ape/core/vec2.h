#ifndef APE_VEC2_H
#define APE_VEC2_H

#include <type_traits>

namespace ape {

    /**
     * A structure which stores a pair of values of numerical type and defines
     * operations to allow quick calculations.
     */
    template<typename T>
    struct Vec2 {
        // This is true for char because of how C/C++ types work...
        static_assert(std::is_arithmetic<T>::value, "Template argument must be a numeric type");
        Vec2() {
            x = y = T();
        }

        Vec2(T xValue, T yValue) :
            x (xValue), y (yValue) { }

        Vec2<T> operator+ (Vec2<T> v) {
            return Vec2<T>( x + v.x, y + v.y );
        }

        // check this
        Vec2<T> operator- (Vec2<T> v) {
            return Vec2<T>( x - v.x, y - v.y );
        }

        Vec2<T> operator* (const T& val) {
            return Vec2<T>(x * val, y * val);
        }

        Vec2<T> operator* (const Vec2<T>& v) {
            return Vec2<T>(x * v.x, y * v.y);
        }

        Vec2<T> operator/ (const T& val) {
            return Vec2<T>(x / val, y / val);
        }

        Vec2<T> operator/ (const Vec2<T>& v) {
            return Vec2<T>(x / v.x, y / v.y);
        }

        Vec2<T>& operator= (const Vec2<T>& v) {
            x = v.x;
            y = v.y;
            return *this;
        }

        Vec2<T>& operator= (const T& val) {
            x = val;
            y = val;
            return *this;
        }

        Vec2<T>& operator+= (const Vec2<T>& v) {
            x += v.x;
            y += v.y;
            return *this;
        }

        Vec2<T>& operator-= (const Vec2<T>& v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        Vec2<T>& operator+= (const T& val) {
            x += val;
            y += val;
            return *this;
        }

        Vec2<T>& operator-= (const T& val) {
            x -= val;
            y -= val;
            return *this;
        }

        bool operator==(const Vec2<T>& val) {
            if((x == val.x) && (y == val.y)) {
                return true;
            }

            return false;
        }

        bool operator!=(const Vec2<T>& val) {
            if((x == val.x) && (y == val.y)) {
                return false;
            }

            return true;
        }

        T x, y;
    };

    using Vec2i = Vec2<int>;
    using Vec2f = Vec2<float>;
    using Vec2u = Vec2<unsigned int>;
}

#endif
