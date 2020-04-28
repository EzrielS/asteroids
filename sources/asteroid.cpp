#include "../headers/asteroid.h"

Asteroid::Asteroid(double x, double y,  std::list<SDL_Surface*> _asteroidsAsSurface, SDL_Renderer* renderer): Entity(x, y,  _asteroidsAsSurface.front(), renderer) {
	this->_asteroidsAsSurface = _asteroidsAsSurface;	// peut etre par copy plutot ?
	this->_asteroidsAsSurface.remove(_asteroidsAsSurface.front());
	this->pivot(rand()%360);
	this->setVitesse(angleToVec(rand()%360) * (rand()%10));
}

Asteroid::Asteroid(Point coords, std::list<SDL_Surface*> _asteroidsAsSurface, SDL_Renderer* renderer): Entity(coords, _asteroidsAsSurface.front(), renderer) {
	this->_asteroidsAsSurface = _asteroidsAsSurface;	// peut etre par copy plutot ?
	this->_asteroidsAsSurface.remove(_asteroidsAsSurface.front());
	this->pivot(rand()%360);
	this->setVitesse(angleToVec(rand()%360) * (rand()%10));
}


Asteroid::~Asteroid() {
	std::cout << "Asteroid destructeur" << std::endl;
	
	if(this->_asteroidsAsSurface.size() > 0) {
		Asteroid* newAst1 = new Asteroid(this->_coords, this->_asteroidsAsSurface, this->_renderer);
		int tmp = rand()%360;
		newAst1->pivot(tmp);
		newAst1->setVitesse(angleToVec(tmp)*10);

		Asteroid* newAst2 = new Asteroid(this->_coords, this->_asteroidsAsSurface, this->_renderer);
		newAst2->pivot(tmp+120);
		newAst2->setVitesse(angleToVec(tmp+120)*10);

		Asteroid* newAst3 = new Asteroid(this->_coords, this->_asteroidsAsSurface, this->_renderer);
		newAst3->pivot(tmp+240);
		newAst3->setVitesse(angleToVec(tmp+240)*10);

		Game::getInstance().entities.push_front(newAst1);
		Game::getInstance().entities.push_front(newAst2);
		Game::getInstance().entities.push_front(newAst3);

	}
}

void Asteroid::update() {
	Entity::update();
}