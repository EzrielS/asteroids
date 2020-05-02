#ifndef __SHIP_H__
#define __SHIP_H__

#include "../sources/bullet.cpp"
#include "weapon.h"

class Ship : public Entity {
    private:
        int _nbVie;
        int _score;
        std::list<Weapon*> _weapons;
        std::list<Bullet*> _bullets;

    public:
        Ship(double x, double y, SDL_Surface* imageAsSurf, SDL_Renderer* renderer, int nbVie);

        std::list<Bullet*> getBullets();

        virtual void update();
        virtual void draw();

        void giveWeapon(Weapon* w);
        int getVie();
        void setVie(int v);
        int getScore();
        std::list<Weapon*> getWeapons();

        void addScore(int nb);

};

#endif