#ifndef __SHIP_H__
#define __SHIP_H__

#include "../sources/entities/entity.h"
#include "bullet.h"
#include <list>

class Ship: public Entity {
    private:
 //       Point _shipHead;
 //       int direction; // TODO Change to Vec2
        int nbVie;


    public:
        Ship(double x, double y, SDL_Surface* imageAsSurf, SDL_Renderer* renderer, int nbVie):
        	Entity(x, y, imageAsSurf, renderer),
        	nbVie(nbVie){}

        virtual void update();
        virtual void draw();
//        double _speed;

//        void draw(SDL_Renderer* renderer);
        void speedUp();
        void slowDown();

        std::list<Bullet*> bullets;
//        void move();
};

#endif