#ifndef __GAME_H__
#define __GAME_H__

#include <list>
#include "bonus.h"
#include "asteroid.h"

class Game
{
    private:
        Game();
        ~Game();
        static Game _instance;


    public:
        Game(Game const&) = delete;
        Game& operator=(Game const&) = delete;
        static Game& getInstance();
        
        SDL_Renderer* _renderer;
        std::list<Entity*> entities;
        std::list<Bonus*> bonuses;

        static void addEntity(Entity *e);

        bool quit = false;

        void update();
        void draw();
        void collisions();
        void init(SDL_Renderer* renderer);
        static void end();
};

#endif