#include "./entity.h"
#include "../../headers/vec2.h"

Entity::Entity(double x, double y, double width, double height, const char* imageFile, SDL_Renderer* renderer){
	this->renderer = renderer;
	this->imageAsSurf = SDL_LoadBMP(imageFile);
	
	if(!this->imageAsSurf){
	    std::cerr << "Erreur de chargement de l'image : " << SDL_GetError() << std::endl;
	    exit (-1);
	}
	this->image = SDL_CreateTextureFromSurface(renderer,this->imageAsSurf);
	this->coords = Point(x, y);
	this->angle=0.;
	this->vitesse=Vec2d(0, 0);
}

void Entity::update(){
	std::cout << "[UNITE UPDATED] w vitesse " << this->vitesse << " @ " << this->coords  << std::endl;
	this->coords = this->coords + this->vitesse;
	if(this->coords.getY() > 1030){
		this->coords.setY(-29);
	}
	if(this->coords.getY() < -30){
		this->coords.setY(1029);
	}
	if(this->coords.getX() > 630){
		this->coords.setX(-29);
	}
	if(this->coords.getX() < -30){
		this->coords.setX(629);
	}
	this->vitesse *= 0.999;
}


void Entity::draw(){
	std::cout << "[UNITE DRAWN]" << std::endl;
	SDL_Rect tmpRect = this->getRect();
	SDL_RenderCopyEx(this->renderer,
                    this->image,
                    NULL,
                    &tmpRect,
                    this->angle,
                    NULL,			// center
                    SDL_FLIP_NONE);
}

SDL_Rect Entity::getRect(){
	SDL_Rect tmpRect;
	tmpRect.x = this->coords.getY();
	tmpRect.y = this->coords.getX();
	SDL_QueryTexture(this->image, NULL, NULL, &tmpRect.w, &tmpRect.h);

	return tmpRect;
}