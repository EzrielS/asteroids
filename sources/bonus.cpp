#include "../headers/bonus.h"


Bonus::Bonus(double x, double y, SDL_Surface* imageAsSurf, SDL_Renderer* renderer){
	this->_renderer = renderer;	
	this->_image = SDL_CreateTextureFromSurface(renderer,imageAsSurf);
	this->_coords = Point(x, y);
}
Bonus::Bonus(Point coords, SDL_Surface* imageAsSurf, SDL_Renderer* renderer){
	this->_renderer = renderer;	
	this->_image = SDL_CreateTextureFromSurface(renderer,imageAsSurf);
	this->_coords = coords;
}

Bonus::~Bonus() {
    SDL_DestroyTexture(this->_image);
}

void doBonus() {

}

void Bonus::draw(){
	SDL_Rect tmpRect = this->getRect();
	SDL_RenderCopyEx(this->_renderer,
                    this->_image,
                    NULL,
                    &tmpRect,
                    0,
                    NULL,			// center
                    SDL_FLIP_NONE);
}

SDL_Rect Bonus::getRect(){
	SDL_Rect tmpRect;
	tmpRect.x = this->_coords.getY();
	tmpRect.y = this->_coords.getX();
	SDL_QueryTexture(this->_image, NULL, NULL, &tmpRect.w, &tmpRect.h);
	tmpRect.x -= tmpRect.w/2;
	tmpRect.y -= tmpRect.h/2;
	return tmpRect;
}