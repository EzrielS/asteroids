#ifndef __GAME_H__
#define __GAME_H__

#include <list>

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

        static void addEntity(Entity *e);

        void update();
        void draw();
        void init(SDL_Renderer* renderer);
        static void end();
};

#endif