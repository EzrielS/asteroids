#include "../../headers/weapon.h"
#include "../../headers/bullet.h"
#include "entities/entity.h"


Weapon::Weapon(SDL_Surface* imageAsSurf, int dmg, double vitesse, int cooldown){
	this->imageAsSurf = imageAsSurf;
	this->dmg = dmg;
	this->vitesse = vitesse;
	this->cooldown = cooldown;
	this->lastUsed=0;
	this->ship = 0;
}

void Weapon::bind(Ship* ship){
	this->ship = ship;
}


void Weapon::fire(){
	std::cout << "Creation de bullet ...\n" ;
	Bullet newBullet = Bullet(this->ship->getCoords().getY(), this->ship->getCoords().getX(), this->imageAsSurf, this->ship->getRenderer(), this->dmg); // ###
	this->ship->bullets.push_front(&newBullet);
	std::cout << "Done " << std::endl;
}

