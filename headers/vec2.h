#ifndef __VEC2_H__
#define __VEC2_H__

#include <string>

template <class T>
class Vec2
{
    public:
        T _x, _y;
	
        Vec2() : _x(0), _y(0) { };
        Vec2(T x, T y) : _x(x), _y(y) { };
        Vec2(const Vec2& v) : _x(v.x), _y(v.y) { };

        Vec2 operator+(Vec2& v) {
            return Vec2(_x + v._x, _y + v._y);
        }

        friend bool operator==(const Vec2& v1, const Vec2& v2) {
            return (v1._x == v2._x && v1._y == v2._y);
        }

        friend bool operator!=(const Vec2& v1, const Vec2& v2) {
            return !(v1 == v2);
        }

        friend std::ostream& operator<<(std::ostream& os, const Vec2& v) {
            os << "[" << v._x << ", " << v._y << "]";
            return os;
        }

};

#endif
