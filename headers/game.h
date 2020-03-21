#ifndef __GAME_H__
#define __GAME_H__

#include "point.h"
#include "ship.h"

class Game
{
    private:
        Game();
        ~Game();
        static Game _instance;

    public:
        Ship _ship;

        Game(Game const&) = delete;
        Game& operator=(Game const&) = delete;
        static Game& getInstance();
        
        void init(SDL_Renderer* renderer);
};

#endif