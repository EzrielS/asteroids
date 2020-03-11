#include "../headers/point.h"

Point::Point() : _x(0.), _y(0.) { }

Point::Point(double x, double y) : _x(x), _y(y) { }

double Point::getX() {
    return _x;
}

double Point::getY() {
    return _y;
}

void Point::setX(double x) {
    this->_x = x;
}

void Point::setY(double y) {
    this->_y = y;
}

Point Point::translation(double translateX, double translateY) {
    return Point(this->_x + translateX, this->_y + translateY);
}