#include "../headers/ship.h"
#include <typeinfo>
// #include "../sources/weapon.cpp"
#include "../headers/weapon.h"



void Ship::speedUp() {
	this->addVitesse(angleToVec(this->getAngle()));		// todo : acceleration
}


void Ship::update(){
	Entity::update();
	for (std::list<Bullet*>::iterator it=this->bullets.begin(); it != this->bullets.end(); ++it){
 		(*it)->update();

        if((*it)->getHealth() <= 0) { // Si la Bullet n'a plus de vie, on la supprime
            this->bullets.erase(it--);
			Game::getInstance().entities.remove(*it);
        }
 	}
	for (std::list<Weapon*>::iterator it=this->weapons.begin(); it != this->weapons.end(); ++it){
 		(*it)->update();
 	}
}


void Ship::draw(){
	Entity::draw();
	for (std::list<Bullet*>::iterator it=this->bullets.begin(); it != this->bullets.end(); ++it){
 		(*it)->draw();
 	}
}

void Ship::giveWeapon(Weapon* w){
	this->weapons.push_front(w);
}
