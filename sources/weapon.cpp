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
	if(this->currentCooldown == 0) {
		Point tmp = this->ship->getCoords();
		Vec2d tmp2 = angleToVec(this->ship->getAngle());
		tmp = tmp + tmp2;
		Bullet* newBullet = new Bullet(tmp.getX(), tmp.getY(), this->imageAsSurf, this->ship->getRenderer(), this->_damage, this->_bulletHealth); // ###
		newBullet->setVitesse(tmp2 * this->vitesse );
		this->ship->bullets.push_front(newBullet);
		this->currentCooldown = this->cooldown;

		Game::addEntity(newBullet);
	// remove tmp & tmp2
	}
}

void Weapon::update(){
	if(this->currentCooldown != 0){
		this->currentCooldown --;
	}
}