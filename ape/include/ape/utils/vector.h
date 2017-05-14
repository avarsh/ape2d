#ifndef VECTOR_H
#define VECTOR_H

#include <type_traits>

namespace ape {

    /**
     * A structure which stores a pair of values of numerical type.
     */
    template<typename T>
    struct Vec2 {
        // This is true for char...
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

        Vec2<T> operator/ (const T& val) {
            return Vec2<T>(x / val, y / val);
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

    struct Vec2i : public Vec2<int> {
        Vec2i() {}
        Vec2i(int xValue, int yValue) :
            Vec2<int>(xValue, yValue) { }

        Vec2i& operator= (const Vec2<int>& v) {
            x = v.x;
            y = v.y;
            return *this;
        }
    };

    struct Vec2f : public Vec2<float> {
        Vec2f() {}
        Vec2f(float xValue, float yValue) :
            Vec2<float>(xValue, yValue) { }

        Vec2f& operator= (const Vec2<float>& v) {
            x = v.x;
            y = v.y;
            return *this;
        }

        Vec2f& operator= (float val) {
            x = val;
            y = val;
            return *this;
        }
    };

    struct Vec2u : public Vec2<unsigned int> {
        Vec2u() {}
        Vec2u(unsigned int xValue, unsigned int yValue) :
            Vec2<unsigned int>(xValue, yValue) { }

        Vec2u& operator= (const Vec2<unsigned int>& v) {
            x = v.x;
            y = v.y;
            return *this;
        }
    };
}

#endif // VECTOR_H
