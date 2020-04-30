#ifndef __BULLET_H__
#define __BULLET_H__

// #include "../headers/ship.h"
#include "../sources/entities/entity.h"

class Ship;

class Bullet : public Entity
{
	private:
		int _damage;
		Ship* _parent;
	public:
		Bullet(double x, double y, SDL_Surface* imageAsSurf, SDL_Renderer* renderer, int damage, int health, Ship* parent);

		~Bullet();

		int getDamage();

		void update();
		Ship* getParent();
}; 

#endif