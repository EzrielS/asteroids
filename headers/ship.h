#ifndef __SHIP_H__
#define __SHIP_H__

#include "point.h"

class Ship
{
    private:
        double _speed;

    public:
        Ship();
        void draw(SDL_Renderer* renderer);
};

#endif