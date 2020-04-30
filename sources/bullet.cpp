#include "../headers/bullet.h"

Bullet::Bullet(double x, double y, SDL_Surface* imageAsSurf, SDL_Renderer* renderer, int damage, int health, Ship* parent) : Entity(x, y,  imageAsSurf, renderer) {
	this->_damage = damage;
	this->_health = health;
	this->_parent = parent;
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

Ship* Bullet::getParent(){
	return this->_parent;
}