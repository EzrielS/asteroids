#include "../headers/game.h"
#include <list>

Game Game::_instance = Game();

Game::Game() { }

Game::~Game() { }

Game& Game::getInstance() {
    return _instance;
}

void Game::init(SDL_Renderer* renderer) {
	_renderer=renderer;
//    _ship = Ship();
}

void Game::addEntity(Entity *e) {
	Game::getInstance().entities.push_front(e);
}

void Game::update(){
	for (std::list<Entity*>::iterator it=this->entities.begin(); it != this->entities.end(); ++it){
		(*it)->update();
	}
}

void Game::draw(){
	for (std::list<Entity*>::iterator it=this->entities.begin(); it != this->entities.end(); ++it){
 		(*it)->draw();
	}
}