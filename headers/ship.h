#ifndef __SHIP_H__
#define __SHIP_H__

#include "point.h"

class Ship
{
    private:
        double _speed;
        Point _shipHead;
        int direction; // TODO Change to Vec2

    public:
        Ship();
        void draw(SDL_Renderer* renderer);
        void speedUp();
        void slowDown();
        void move();
};

#endif