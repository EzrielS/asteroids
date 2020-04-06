#include "../../headers/weapon.h"
#include "../../headers/bullet.h"
#include "entities/entity.h"


Weapon::Weapon(SDL_Surface* imageAsSurf, int damage, double vitesse, int cooldown, int bulletHealth){
	this->imageAsSurf = imageAsSurf;
	this->_damage = damage;
	this->vitesse = vitesse;
	this->cooldown = cooldown;
	this->lastUsed=0;
	this->ship = 0;
	this->_bulletHealth = bulletHealth;
}

void Weapon::bind(Ship* ship){
	this->ship = ship;
	ship->giveWeapon(this);
}


void Weapon::fire(){
	if(this->currentCooldown == 0){
		Bullet* newBullet = new Bullet(this->ship->getCoords().getX(), this->ship->getCoords().getY(), this->imageAsSurf, this->ship->getRenderer(), this->_damage, this->_bulletHealth); // ###
		newBullet->setVitesse( angleToVec(this->ship->getAngle()) * this->vitesse );
		this->ship->bullets.push_front(newBullet);
		this->currentCooldown = this->cooldown;
	}
}

void Weapon::update(){
	if(this->currentCooldown != 0){
		this->currentCooldown --;
	}
}