#include "../headers/ship.h"

Ship::Ship(double x, double y, SDL_Surface* imageAsSurf, SDL_Renderer* renderer, int nbVie) :
	Entity(x, y, imageAsSurf, renderer), _nbVie(nbVie), _score(0) { }

std::list<Bullet*> Ship::getBullets() {
	return this->_bullets;
}

void Ship::update() {
	Entity::update();
	for (std::list<Bullet*>::iterator it=this->_bullets.begin(); it != this->_bullets.end(); ++it) {
		(*it)->update();

		if((*it)->getHealth() <= 0) { // Si la Bullet n'a plus de vie, on la supprime
			this->_bullets.erase(it--);
			Game::getInstance().entities.remove(*it);
		}
	}

	for (std::list<Weapon*>::iterator it=this->_weapons.begin(); it != this->_weapons.end(); ++it) {
		(*it)->update();
	}
}

void Ship::draw() {
	Entity::draw();

	for (std::list<Bullet*>::iterator it=this->_bullets.begin(); it != this->_bullets.end(); ++it) {
		(*it)->draw();
	}
}

void Ship::giveWeapon(Weapon* w) {
	this->_weapons.push_front(w);
}

std::list<Weapon*> Ship::getWeapons() {
	return this->_weapons;
}

int Ship::getVie(){
	return this->_nbVie;
}

void Ship::setVie(int v) {
	this->_nbVie = v;
}

int Ship::getScore(){
	return this->_score;
}

void Ship::addScore(int nb){
	this->_score+= nb;
}
