#include <SDL.h>
#include <iostream>
#include <cassert>

#include "../projet/sources/point.cpp"
#include "../projet/sources/ship.cpp"

void draw(SDL_Renderer* renderer)
{
	int x,y;
	if ( SDL_GetMouseState(&x,&y) & SDL_BUTTON(SDL_BUTTON_LEFT) ) // one & it is for bits AND
	{
		// UTILISER COLOR
		Ship s = Ship();
		s.draw(renderer);
		SDL_SetRenderDrawColor(renderer, 255,255,255,255);
		SDL_RenderDrawPoint(renderer,x,y);
	}
}



int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "Pb init SDL"<< std::endl;
		return 0;
	}

	SDL_Window* window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 600,
						  SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	assert (renderer != nullptr);

/*
	Point toto = Point(10., 20.);
	std::cout << "Point : " << toto.getX() << " : " << toto.getY() << std::endl;
	Point titi = toto.translation(2., 3.);
	std::cout << "Point : " << titi.getX() << " : " << titi.getY() << std::endl;
*/

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		while (!quit && SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			}
		}

		draw(renderer);
		SDL_RenderPresent(renderer);
	}
	SDL_Quit();

	return 0;
}
