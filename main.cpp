#include <SDL.h>
#include <iostream>
#include <cassert>
#include <chrono>
#include <thread>

#include "sources/point.cpp"
#include "sources/ship.cpp"
#include "sources/weapon.cpp"
#include "sources/game.cpp"
#include "headers/vec2.h"
#include "sources/entities/entity.cpp"

#include <math.h>  


void draw(SDL_Renderer* renderer)
{
	int x,y;
	if ( SDL_GetMouseState(&x,&y) & SDL_BUTTON(SDL_BUTTON_LEFT) ) // one & it is for bits AND
	{
		//Ship s = Ship();
		//s.draw(renderer);
		// UTILISER COLOR
		SDL_SetRenderDrawColor(renderer, 255,255,255,255);
		SDL_RenderDrawPoint(renderer,x,y);
	}
}


SDL_Surface* getImageAsSurface(const char * file){
	SDL_Surface* ret = SDL_LoadBMP(file);
	if(!ret){
	    std::cerr << "Erreur de chargement de l'image : " << SDL_GetError() << std::endl;
	    exit (-1);
	}
	return ret;
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

	Point p1 = Point(10,10);
	Vec2d v1(5,6);
	Vec2<double> v2(5,10);
	Vec2<double> v3 = v1 + v2;
	Vec2<double> v4 = Vec2d::normalize(v1);

	v1.set(15,30);

	std::cout << "v1 = " << v1 << std::endl;
	std::cout << "v2 = " << v2 << std::endl;
	std::cout << "v3 = " << v3 << std::endl;
	std::cout << "v4 = " << v4 << std::endl;

	std::cout << "v1 == v2 = " << (v1==v2) << std::endl;


	
	// std::cout << "[" << v._x << ", " << v._y << "]" << std::endl;

Ship e  = Ship(300, 500, getImageAsSurface("images/vaisseau.bmp"), renderer, 10);
e.setInertie(0.999);
g.entities.push_front(&e);


Weapon w1 = Weapon(
	getImageAsSurface("images/tir1.bmp"), 
	1,   // dmg
	30,  // vitesse
	5,	 // cooldown
	50); // bullet health
w1.bind(&e);

	std::cout << "P1 = " << p1 << std::endl;
	std::cout << "P1 + v3 = " << (p1+v3) << std::endl;

	
	// std::cout << "[" << v._x << ", " << v._y << "]" << std::endl;

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
							std::cout << "Key Left !" << std::endl;
e.pivot(-90/5);
							break;
						case SDLK_RIGHT:
							std::cout << "Key Right !" << std::endl;
e.pivot(90/5);
							break;
						case SDLK_UP:
							std::cout << "Key Up !" << std::endl;
e.addVitesse(angleToVec(e.getAngle()));
//e.vitesse =  Vec2d(sin(e.angle*(2*M_PI/360)), cos(e.angle*(2*M_PI/360))) + e.vitesse ;
//							g._ship.speedUp();
							break;
						case SDLK_DOWN:
							std::cout << "Key Down !" << std::endl;
//							g._ship.slowDown();
							break;
						case SDLK_SPACE	:
							std::cout << "FIRE !" << std::endl;
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

//		g._ship.move();
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		g.update();
		g.draw();
//e.update();
//e.draw();
//std::cout << "speed is : " << e.vitesse << "with angle " << e.angle << " @ " << e.coords << std::endl ;



//		g._ship.draw(renderer);


    	SDL_RenderPresent(renderer);


		draw(renderer);
		SDL_RenderPresent(renderer);
		std::this_thread::sleep_for(std::chrono::milliseconds(25));

	}
	SDL_Quit();

	return 0;
}
