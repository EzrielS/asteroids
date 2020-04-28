#ifndef __WEAPON_H__
#define __WEAPON_H__

class Ship;

#include "../headers/game.h"

class Weapon
{
    private:
		int _lastUsed;
		int _damage;
		SDL_Surface* _imageAsSurf;
		double _vitesse;
		int _cooldown;
		int _currentCooldown = 0;
		int _bulletHealth;
		Ship* _ship;

	public:
		Weapon(SDL_Surface* imageAsSurf, int damage, double vitesse, int cooldown, int bulletHealth);
		void fire();
		void bind(Ship* ship);
		void update();
};

#endif