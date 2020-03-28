

#ifndef __WEAPON_H__
#define __WEAPON_H__

class Entity;
class Ship;
// #include "../sources/ship.cpp"


class Weapon
{
    private:

	 	int lastUsed;
		int dmg;
    	SDL_Surface* imageAsSurf;
		double vitesse;
		int cooldown;
    	int currentCooldown;
		Ship* ship;

    	
    public:
    	Weapon(SDL_Surface* imageAsSurf, int dmg, double vitesse, int cooldown);
    	void fire();
    	void bind(Ship* ship);
    	void update();

};

#endif