#include "../sources/entities/entity.h"

#ifndef __ASTEROID_H__
#define __ASTEROID_H__

class Asteroid : public Entity
{
    private:

    	int _damage;


    public:
    	std::list<SDL_Surface*> asteroidsAsSurface;
    	Asteroid(double x, double y,  std::list<SDL_Surface*> asteroidsAsSurface, SDL_Renderer* renderer): Entity(x, y,  asteroidsAsSurface.front(), renderer)
    			{
    				this->asteroidsAsSurface = asteroidsAsSurface;	// peut etre par copy plutot ?
    				this->asteroidsAsSurface.remove(asteroidsAsSurface.front());
    				this->pivot(rand()%360);
    				this->setVitesse(angleToVec(rand()%360) * (rand()%10));
    			}



}; 

#endif