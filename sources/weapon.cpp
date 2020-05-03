#include "../../headers/weapon.h"

Weapon::Weapon(SDL_Surface* imageAsSurf, int damage, double vitesse, int cooldown, int bulletHealth){
	this->_imageAsSurf = imageAsSurf;
	this->_damage = damage;
	this->_vitesse = vitesse;
	this->_cooldown = cooldown;
	this->_lastUsed = 0;
	this->_ship = 0;
	this->_bulletHealth = bulletHealth;
}

double Weapon::getVitesse() {
	return this->_vitesse;
}

void Weapon::setVitesse(double v) {
	this->_vitesse = v;
}

void Weapon::bind(Ship* ship){
	this->_ship = ship;
	this->_ship->giveWeapon(this);
}

void Weapon::fire(){
	if(this->_currentCooldown == 0) {
		Point tmp = this->_ship->getCoords();
		Vec2d tmp2 = angleToVec(this->_ship->getAngle());
		tmp = tmp + tmp2;
		Bullet* newBullet = new Bullet(tmp.getX(), tmp.getY(), this->_imageAsSurf, this->_ship->getRenderer(), this->_damage, this->_bulletHealth, this->_ship);
		newBullet->setVitesse(tmp2 * this->_vitesse );
		this->_ship->getBullets().push_front(newBullet);
		this->_currentCooldown = this->_cooldown;

		Game::addEntity(newBullet);
	}
}

void Weapon::update(){
	if(this->_currentCooldown != 0) {
		(this->_currentCooldown)--;
	}
}
SDL_Surface* getImageAsSurface(const char * file);

Weapon getGatling(){
	return Weapon(
		getImageAsSurface("images/tir1.bmp"),
		40,   // dmg
		9.5,  // vitesse
		5,	 // cooldown
		50); // bullet health
}

Weapon getLanceRocket(){
	return Weapon(
		getImageAsSurface("images/tir2.bmp"), 
		100,   // dmg
		6,  // vitesse
		50,	 // cooldown
		175); // bullet health
}
