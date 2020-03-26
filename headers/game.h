#ifndef __GAME_H__
#define __GAME_H__

#include <list> 

#include "point.h"
#include "ship.h"
#include "../sources/entities/entity.h"

class Game
{
    private:
        Game();
        ~Game();
        static Game _instance;

    public:
//        Ship _ship;

        Game(Game const&) = delete;
        Game& operator=(Game const&) = delete;
        static Game& getInstance();
        
        SDL_Renderer* _renderer;
        std::list<Entity*> entities;

        void update();
        void draw();
        void init(SDL_Renderer* renderer);
};

#endif