#include "../headers/game.h"

Game Game::_instance = Game();

Game::Game() { }

Game::~Game() { }

Game& Game::getInstance() {
    return _instance;
}

void Game::init(SDL_Renderer* renderer) {
    _ship = Ship();
}