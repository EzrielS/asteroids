#include <SDL.h>
#include <iostream>
#include <cassert>
#include <chrono>
#include <thread>

#include "sources/point.cpp"
#include "sources/ship.cpp"
#include "sources/weapon.cpp"
#include "sources/bonus.cpp"
#include "sources/game.cpp"
#include "sources/asteroid.cpp"
#include "headers/vec2.h"
#include "sources/entities/entity.cpp"
#include "sources/print_string.cpp"

#include <math.h>  
#include <time.h>


SDL_Surface* getImageAsSurface(const char * file){
	SDL_Surface* ret = SDL_LoadBMP(file);
	if(!ret){
		std::cerr << "Erreur de chargement de l'image : " << SDL_GetError() << std::endl;
		exit (-1);
	}
	SDL_SetColorKey(ret, SDL_TRUE, SDL_MapRGB(ret->format, 0, 0, 0));
	return ret;
}


int main(int argc, char** argv)
{
	srand(time(NULL));
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		return 0;
	}

	SDL_Window* window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 600,
						  SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	assert (renderer != nullptr);

	Game& g = Game::getInstance();
	g.init(renderer);


	Ship e = Ship(300, 500, getImageAsSurface("images/vaisseau2.bmp"), renderer, 10);
	e.setInertie(0.999);
	g.entities.push_front(&e);

	Weapon w1 = getGatling();
	Weapon w2 = getLanceRocket();

	w1.bind(&e);
	w2.bind(&e);

	Asteroid a1 = Asteroid(	400, 400, std::list<SDL_Surface*> { getImageAsSurface("images/asteroide1.bmp"),
		getImageAsSurface("images/asteroide2.bmp"), getImageAsSurface("images/asteroide3.bmp") }, renderer);
	g.entities.push_front(&a1);

	bool quit = false;
	bool hard_quit = false;

	bool bonusActivated = false;
	bool shipInvincible = false;
//	std::list<Bonus*> g.bonuses;

	while (!g.quit)
	{
		SDL_RenderClear(renderer);
		SDL_Event event;
		while (!quit && SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_KEYDOWN:
					switch( event.key.keysym.sym ){
						case SDLK_LEFT:
							e.pivot(-90/5);
							break;
						case SDLK_RIGHT:
							e.pivot(90/5);
							break;
						case SDLK_UP:
							e.speedUp(angleToVec(e.getAngle()));
							break;
						case SDLK_DOWN:
							e.slowDown(angleToVec(e.getAngle()));
							break;
						case SDLK_LCTRL:
							w1.fire();
							break;
						case SDLK_SPACE	:
							w2.fire();
							break;
						default:
							break;
					}
					break;
				case SDL_QUIT:
					g.quit = true;
					hard_quit = true;
					break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

/*
 *	print_hud - à separer à terme
 *
*/

		print_str("Nombre de vies : " + std::to_string(e.getVie()) + "   Score : " +  std::to_string(e.getScore()), Point(0, 0));

//////////////////////


		g.update();

		if((rand() % 1000) == 0){
				Bonus* newBonus = new Bonus(rand()%600, rand()%1000, getImageAsSurface("images/attackspeed_bonus.bmp"), renderer );
				g.bonuses.push_front(newBonus);
		}


		for (std::list<Bonus*>::iterator it=g.bonuses.begin(); it != g.bonuses.end(); ++it) {
			(*it)->draw();
		}

		g.collisions();

		g.draw();
    	SDL_RenderPresent(renderer);
		std::this_thread::sleep_for(std::chrono::milliseconds(25));

	}

	if(!hard_quit)
		std::this_thread::sleep_for(std::chrono::seconds(10));

	SDL_Quit();

	exit(0);
}
