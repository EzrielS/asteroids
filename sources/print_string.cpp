#ifndef __PRINTSTR__
#define __PRINTSTR__

#include "../headers/game.h"
#include "../headers/point.h"
#include "./simplex.cpp"


int print_char(char c, Point p){
	Game& game = Game::getInstance();
	if (c < 32 || c > 126)
		std::cout << "Fatal error : this char cannot be printed (" << c << ")" << std::endl;
	c = c-' ';
	int absX = p .getX();
	int absY = p .getY() + 25;

	int x = simplex[c][2];
	int y = simplex[c][3];
	bool isLeve = false;
	for(int i = 4; i < simplex[c][0] * 2 + 4; i+=2){
		if(simplex[c][i] == -1 && simplex[c][i+1] == -1){
			isLeve = true;
		}
		else{
			if(! isLeve){
				SDL_RenderDrawLine(game._renderer, absX + x, absY - y, absX + simplex[c][i], absY - simplex[c][i+1]);
			}
			else{
				isLeve = false;
			}
			x = simplex[c][i];
			y = simplex[c][i+1];
		}
	}
	return simplex[c][1];
}

int print_str(std::string s, Point p){
	int decal = 0;
	for (auto it=s.begin(); it != s.end(); ++it) {
		decal += print_char(*it, Point(p.getX()+decal, p.getY()));
	}
	return decal;
}

#endif
