#include "../sources/entities/entity.h"

#ifndef __BULLET_H__
#define __BULLET_H__

class Bullet  : public Entity
{
    private:

    	int dmg;


    public:

    	Bullet(double x, double y, SDL_Surface* imageAsSurf, SDL_Renderer* renderer, int dmg): Entity(x, y,  imageAsSurf, renderer)
    			{
    				this->dmg = dmg;
    			}

//    	Bullet(double x, double y, SDL_Surface* imageAsSurf, SDL_Renderer* renderer, int dmg);

    	int getDmg();

}; 

#endif