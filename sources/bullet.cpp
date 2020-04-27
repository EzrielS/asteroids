#include "../headers/bullet.h"
#include "../sources/entities/entity.h"


Bullet::Bullet(double x, double y, SDL_Surface* imageAsSurf, SDL_Renderer* renderer, int damage, int health) : Entity(x, y,  imageAsSurf, renderer) {
	this->_damage = damage;
	this->_health = health;
}

Bullet::~Bullet() {
	std::cout << "Bullet destructeur" << std::endl;
}

int Bullet::getDamage(){
	return this->_damage;
}

void Bullet::update() {
	Entity::update();

	(this->_health)--;
}