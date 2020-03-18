#ifndef __POINT_H__
#define __POINT_H__

#include "vec2.h"

class Point 
{
    private:
        double _x;
        double _y;

    public:
        Point();
        Point(double x, double y);
        void setX(double x);
        void setY(double y);
        double getX();
        double getY();
        Point translation(double translateX, double translateY);
        inline Point operator+(Vec2d& v) {
            return Point(double(_x + v[0]), double(_y + v[1]));
        }
        friend std::ostream& operator<<(std::ostream& os, const Point& p) {
            os << "Point[" << p._x << ", " << p._y << "]";
            return os;
        }
};

#endif