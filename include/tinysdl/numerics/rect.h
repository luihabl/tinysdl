#pragma once

#include "tinysdl/numerics/matrix.h"

namespace TinySDL{

    template <typename T>
    struct TRect {
        
        T x = 0, y = 0;
        T w = 0, h = 0;

        TRect() = default;
        TRect(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {}
        TRect(const Vec4 & v) : x(v[0]), y(v[1]), w(v[2]), h(v[3]) {}

        operator Vec4() const {return Vec4{x, y, w, h};}
        
        bool overlaps(const TRect & o) {
            return  (x < (o.x + o.w)) && ((x + w) > o.x) &&
                    (y < (o.y + o.h)) && ((y + h) > o.y);
        }

        TRect operator+(const Vec<T, 2> & vec) {
            return {x + vec[0] , y + vec[1], w, h};
        }

        template <typename G>
        TRect<G> cast_to() const {
            return {(G) x, (G) y, (G) w, (G) h};
        }
    };

    typedef TRect<float> Rect;
    typedef TRect<int> IntRect;

}
