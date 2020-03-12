#ifndef __GAME_H__
#define __GAME_H__

#include "point.h"
#include "ship.h"

class Game
{
    private:

    public:
       Ship _ship;

        Game();
        void init(SDL_Renderer* renderer);
};

#endif