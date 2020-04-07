#include "../headers/asteroid.h"


//Asteroid(double x, double y,  std::list<SDL_Surface*> asteroidsAsSurface, SDL_Renderer* renderer): Entity(x, y,  asteroidsAsSurface.front(), renderer)


void Asteroid::update(){
	Entity::update();


///  pour le test
	this->_health--;
	if (this->_health == 0){
		this->~Asteroid();
	}
////


}

Asteroid::~Asteroid(){
		if(this->asteroidsAsSurface.size() > 0){
			Asteroid* newAst1 = new Asteroid(this->coords, this->asteroidsAsSurface, renderer);
			newAst1->pivot(30);
			newAst1->setVitesse(angleToVec(30)*10);
			Asteroid* newAst2 = new Asteroid(this->coords, this->asteroidsAsSurface, renderer);
			newAst2->pivot(30+120);
			newAst2->setVitesse(angleToVec(30+120)*10);
			Asteroid* newAst3 = new Asteroid(this->coords, this->asteroidsAsSurface, renderer);
			newAst3->pivot(30+120+120);
			newAst3->setVitesse(angleToVec(30+120+120)*10);	

			Game::getInstance().entities.push_front(newAst1);
			Game::getInstance().entities.push_front(newAst2);
			Game::getInstance().entities.push_front(newAst3);
		}
}