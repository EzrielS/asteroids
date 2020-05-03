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

void removeInvincibilityAfter2Seconds(bool& b) {
	std::this_thread::sleep_for (std::chrono::seconds(2));
	b = false;
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
	std::list<Bonus*> bonuses;

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
					quit = true;
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
				bonuses.push_front(newBonus);
		}


		for (std::list<Bonus*>::iterator it=bonuses.begin(); it != bonuses.end(); ++it) {
			(*it)->draw();
		}



		for (std::list<Entity*>::iterator it=g.entities.begin(); it != g.entities.end(); ++it) { // Pour chaque entité

			if (dynamic_cast<Asteroid*>(*it) != 0) { // Pour chaque asteroid
				Asteroid* tempAsteroid = dynamic_cast<Asteroid*>(*it);

				for (std::list<Entity*>::iterator it2=g.entities.begin(); it2 != g.entities.end(); ) { // On le compare avec les autres entités

					bool bRemoved = false;

					if(it != it2) { // On vérifie que ce n'est pas lui-même

						if (dynamic_cast<Ship*>(*it2) != 0) { // Si l'entité est un vaisseau
							Ship* tempShip = dynamic_cast<Ship*>(*it2);

							if(tempShip->getVie() <= 0) {
								g.draw();
								Game::end();
								quit = true;
								print_str("You have lost", Point(375,250));
								print_str("Closing in 10 seconds...", Point(300,300));
							}
						
							if(!shipInvincible && checkCollisions( tempAsteroid->getRect(), tempShip->getRect() )) {  // S'il touche un vaisseau
								std::cout << "Vaisseau touché par un asteroid" << std::endl;

								tempShip->setVie(tempShip->getVie() - 1); // Le vaisseau perd 1 point de vie

								// Le vaisseau est invincible pndant 2 secondes après être touché.
								// Un thread s'occupe de modifier le booléen après 2 secondes pour ne pas bloquer le jeu.
								shipInvincible = true;
								std::thread t1(removeInvincibilityAfter2Seconds, std::ref(shipInvincible));
								t1.detach();
							}

						} else if (dynamic_cast<Bullet*>(*it2) != 0) { // Si l'entité est une balle
							Bullet* tempBullet = dynamic_cast<Bullet*>(*it2);

							if(checkCollisions( tempAsteroid->getRect(), tempBullet->getRect() )) {  // S'il touche une bullet
								std::cout << "Asteroid touché par une bullet" << std::endl;

								tempAsteroid->gotHit(tempBullet->getDamage()); // L'asteroid prend les dégats de la balle
								tempBullet->getParent()->addScore(1);
								(*it2)->~Entity();
								it2 = g.entities.erase(it2);
								bRemoved = true;
							}
						}
					}
					if(!bRemoved){
						++it2;
					}
				}
				
			} else if(dynamic_cast<Ship*>(*it) != 0) {  // Pour chaque vaisseau
				Ship* tempShip = dynamic_cast<Ship*>(*it);

				auto bon_it=bonuses.begin();
				while(bon_it != bonuses.end()){
					Bonus* tmpBonus = *bon_it;
					if(checkCollisions( tempShip->getRect(), tmpBonus->getRect())){
						std::cout << "Bonus touché par un Ship" << std::endl;
						double vitesse = tempShip->getWeapons().front()->getVitesse();
						tempShip->getWeapons().front()->setVitesse(vitesse*2);
						delete tmpBonus;
						bon_it = bonuses.erase(bon_it);
					}
					else{
						bon_it++;
					}
				}
			}

				/*if(!bonusActivated && checkCollisions( tempShip->getRect(), bonusAttackSpeed.getRect() )) {  // S'il touche un bonus
					std::cout << "Bonus touché par un Ship" << std::endl;
					double vitesse = tempShip->getWeapons().front()->getVitesse();
					tempShip->getWeapons().front()->setVitesse(vitesse*2);
					bonusAttackSpeed.~Bonus();
					bonusActivated = true;
				}*/


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

	if(!hard_quit)
		std::this_thread::sleep_for(std::chrono::seconds(10));

	SDL_Quit();

	exit(0);
}
