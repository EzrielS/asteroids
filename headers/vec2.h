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

        friend std::ostream& operator<<(std::ostream& os, Vec2 const& v) {
            os << "[" << v._x << ", " << v._y << "]";
            return os;
        }

};

#endif
