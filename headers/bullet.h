#ifndef __BULLET_H__
#define __BULLET_H__

#include "../sources/entities/entity.h"

class Bullet : public Entity
{
	private:
		int _damage;

	public:
		Bullet(double x, double y, SDL_Surface* imageAsSurf, SDL_Renderer* renderer, int damage, int health);

		~Bullet();

		int getDamage();

		void update();
}; 

#endif