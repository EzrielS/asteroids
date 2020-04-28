#include <SDL.h>
#include <iostream>
#include <cassert>
#include <chrono>
#include <thread>

#include "sources/point.cpp"
#include "sources/ship.cpp"
#include "sources/weapon.cpp"
#include "sources/game.cpp"
#include "sources/asteroid.cpp"
#include "headers/vec2.h"
#include "sources/entities/entity.cpp"

#include <math.h>  

/* A DELETE
void draw(SDL_Renderer* renderer)
{
	int x,y;
	if ( SDL_GetMouseState(&x,&y) & SDL_BUTTON(SDL_BUTTON_LEFT) ) // one & it is for bits AND
	{
		SDL_SetRenderDrawColor(renderer, 255,255,255,255);
		SDL_RenderDrawPoint(renderer,x,y);
	}
}
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

bool checkCollisions(SDL_Rect A, SDL_Rect B) {
	//Les côtés des rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
 
    //Calcul les côtés du rectangle A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
 
    //Calcul les côtés du rectangle B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

	//Tests de collisions
    if( bottomA <= topB ) {
        return false;
    }
 
    if( topA >= bottomB ) {
        return false;
    }
 
    if( rightA <= leftB ) {
        return false;
    }
 
    if( leftA >= rightB ) {
        return false;
    }
 
    //Si collision détectée
    return true;
}

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		return 0;
	}

	SDL_Window* window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 600,
						  SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	assert (renderer != nullptr);

	Game& g = Game::getInstance();
	g.init(renderer);


	Ship e  = Ship(300, 500, getImageAsSurface("images/vaisseau2.bmp"), renderer, 10);
	e.setInertie(0.999);
	g.entities.push_front(&e);


	Weapon w1 = Weapon(
		getImageAsSurface("images/tir1.bmp"), 
		100,   // dmg
		15,  // vitesse
		5,	 // cooldown
		50); // bullet health
	w1.bind(&e);

	Asteroid a1 = Asteroid(	400, 400, std::list<SDL_Surface*> { getImageAsSurface("images/asteroide1.bmp"),
		getImageAsSurface("images/asteroide1.bmp"), getImageAsSurface("images/asteroide1.bmp") }, renderer);
	g.entities.push_front(&a1);

	bool quit = false;

	while (!quit)
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
						case SDLK_SPACE	:
							w1.fire();
							break;
						default:
							break;
					}
					break;
				case SDL_QUIT:
					quit = true;
					break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		g.update();


		for (std::list<Entity*>::iterator it=g.entities.begin(); it != g.entities.end(); ++it) { // Pour chaque entité

			if (dynamic_cast<Asteroid*>(*it) != 0) { // Pour chaque asteroid

				for (std::list<Entity*>::iterator it2=g.entities.begin(); it2 != g.entities.end(); ++it2) { // On le compare avec les autres entités
					if(it != it2) { // On vérifie que ce n'est pas lui-même

						if (dynamic_cast<Ship*>(*it2) != 0) { // Si l'entité est un vaisseau
							Ship* tempShip = dynamic_cast<Ship*>(*it2);
						
							if(checkCollisions( (*it)->getRect(), tempShip->getRect() )) {  // S'il touche un vaisseau
								std::cout << "Vaisseau touché par un asteroid" << std::endl;
							}

						} else if (dynamic_cast<Bullet*>(*it2) != 0) { // Si l'entité est une balle
							Bullet* tempBullet = dynamic_cast<Bullet*>(*it2);
							// std::cout << (*it2)->getHealth() << std::endl;

							if(checkCollisions( (*it)->getRect(), tempBullet->getRect() )) {  // S'il touche une bullet
								std::cout << "Asteroid touché par une bullet" << std::endl;

								(*it)->gotHit(tempBullet->getDamage()); // L'asteroid prend les dégats de la balle

								tempBullet->gotHit(tempBullet->getHealth()); // La balle se suicide
							}

						}

					}
				}
				
			}


			if((*it)->getHealth() <= 0) { // Si l'entité n'a plus de vie, on l'a supprime
				(*it)->~Entity();
				g.entities.erase(it--);
			}

		}

		g.draw();

    	SDL_RenderPresent(renderer);


//		draw(renderer);
//		SDL_RenderPresent(renderer);
		std::this_thread::sleep_for(std::chrono::milliseconds(25));

	}
	SDL_Quit();

	return 0;
}
