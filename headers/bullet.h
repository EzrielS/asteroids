#include "../sources/entities/entity.h"

#ifndef __BULLET_H__
#define __BULLET_H__

class Bullet  : public Entity
{
    private:

    	int dmg;


    public:

    	Bullet(double x, double y, SDL_Surface* imageAsSurf, SDL_Renderer* renderer, int dmg):
    		Entity(x, y,  imageAsSurf,  renderer),
    		dmg(dmg) {std::cout << "creation d'une bullet \n";}

    	int getDmg();

}; 

#endif