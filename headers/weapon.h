

#ifndef __WEAPON_H__
#define __WEAPON_H__

class Entity;
class Ship;
// #include "../sources/ship.cpp"


class Weapon
{
    private:

	 	int lastUsed;
		int _damage;
    	SDL_Surface* imageAsSurf;
		double vitesse;
		int cooldown;
    	int currentCooldown = 0;
		int _bulletHealth;
		Ship* ship;

    	
    public:
    	Weapon(SDL_Surface* imageAsSurf, int damage, double vitesse, int cooldown, int bulletHealth);
    	void fire();
    	void bind(Ship* ship);
    	void update();

};

#endif