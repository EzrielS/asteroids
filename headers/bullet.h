#include "../sources/entities/entity.h"

#ifndef __BULLET_H__
#define __BULLET_H__

class Bullet : public Entity
{
    private:

    	int _damage;


    public:

    	Bullet(double x, double y, SDL_Surface* imageAsSurf, SDL_Renderer* renderer, int damage, int health): Entity(x, y,  imageAsSurf, renderer)
    			{
    				this->_damage = damage;
					this->_health = health;
    			}

    	int getDamage();

		void update(){
			Entity::update();
			
			(this->_health)--;
		}

}; 

#endif