#include "../headers/game.h"

Game::Game() { }

void Game::init(SDL_Renderer* renderer) {
    _ship = Ship();
}