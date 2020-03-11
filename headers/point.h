#ifndef __POINT_H__
#define __POINT_H__

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
};

#endif