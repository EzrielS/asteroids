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

/**
 * Conversion d'une image en SDL_Surface
 * @param file Le lien vers une image
 * @return la SDL_Surface créée à partir de cette image
 */
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

	// Création de la fenêtre
	SDL_Window* window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 600,
						  SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	assert (renderer != nullptr);

	// Création de la partie
	Game& g = Game::getInstance();
	g.init(renderer);

	//Création du vaisseau
	Ship e = Ship(300, 500, getImageAsSurface("images/vaisseau.bmp"), renderer, 10);
	e.setInertie(0.999);
	g.entities.push_front(&e); // On ajoute le vaisseau dans la liste des entités

	// Création de deux armes
	Weapon w1 = getGatling();
	Weapon w2 = getLanceRocket();

	// Association des armes avec le vaisseau
	w1.bind(&e);
	w2.bind(&e);

	// Création d'un asteroid
	Asteroid a1 = Asteroid(	400, 400, std::list<SDL_Surface*> { getImageAsSurface("images/asteroide1.bmp"),
		getImageAsSurface("images/asteroide2.bmp"), getImageAsSurface("images/asteroide3.bmp") }, renderer);
	g.entities.push_front(&a1); // On ajoute l'asteroid dans la liste des entités

	// Booléens de vérification
	bool hard_quit = false;
	bool bonusActivated = false;

	while (!g.quit)
	{
		SDL_RenderClear(renderer);
		SDL_Event event;
		// On écoute les touches appuyées
		while (!g.quit && SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_KEYDOWN:
					switch( event.key.keysym.sym ){
						case SDLK_LEFT: // Le vaisseau pivote sur la gauche
							e.pivot(-90/5);
							break;
						case SDLK_RIGHT: // Le vaisseau pivote sur la droite
							e.pivot(90/5);
							break;
						case SDLK_UP: // Le vaisseau accélère
							e.speedUp(angleToVec(e.getAngle()));
							break;
						case SDLK_DOWN: // Le vaisseau ralentit
							e.slowDown(angleToVec(e.getAngle()));
							break;
						case SDLK_SPACE: // On tire avec l'arme primaire
							w1.fire();
							break;
						case SDLK_LCTRL: // On tire avec l'arme secondaire
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

		// On reset l'écran
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

		// Affiche de l'HUD
		print_str("Health : " + std::to_string(e.getVie()) + "   Score : " +  std::to_string(e.getScore()), Point(0, 0));

		g.update(); // On update la position des entités

		// Ajout d'un bonus aléatoirement
		if((rand() % 1000) == 0){
				Bonus* newBonus = new Bonus(rand()%600, rand()%1000, getImageAsSurface("images/attackspeed_bonus.bmp"), renderer );
				g.bonuses.push_front(newBonus);
		}

		// On vérifie les collisions entre les entités
		g.collisions();

		// On dessine les entités
		g.draw();
		SDL_RenderPresent(renderer);

		// On attend 25ms avant de recommencer
		std::this_thread::sleep_for(std::chrono::milliseconds(25));
	}

	// On attend 10 secondes après la fin d'une partie pour quitter
	if(!hard_quit)
		std::this_thread::sleep_for(std::chrono::seconds(10));

	SDL_Quit();

	exit(0);
}
