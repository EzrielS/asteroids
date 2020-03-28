#ifndef __SHIP_H__
#define __SHIP_H__

#include "../sources/entities/entity.h"
#include "../sources/bullet.cpp"
#include "weapon.h"

#include <list>

class Ship: public Entity {
    private:
 //       Point _shipHead;
 //       int direction; // TODO Change to Vec2
        int nbVie;
        std::list<Weapon*> weapons;


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
        void giveWeapon(Weapon* w);

        std::list<Bullet*> bullets;
//        void move();
};

#endif