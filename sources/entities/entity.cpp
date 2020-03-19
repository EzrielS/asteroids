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
	this->coords = this->coords + this->vitesse; 
//	this->coords.setX(this->coords.getX() + this->vitesse._x);
//	this->coords.setY(this->coords.getY() + this->vitesse._y);
}


void Entity::draw(){
	SDL_Rect tmpRect = this->getRect();
	SDL_Rect position;
	position.y = this->coords.getX();
	position.x = this->coords.getY();
std::cout << "when draw coords are " << this->coords.getX() << "-" << this->coords.getY() << std::endl;
	SDL_QueryTexture(this->image, NULL, NULL, &position.w, &position.h);

SDL_RenderCopyEx(this->renderer,
                    this->image,
                    NULL,
                    &position,
                    this->angle,
                    NULL,			// center
                    SDL_FLIP_NONE);
}

SDL_Rect Entity::getRect(){
	SDL_Rect tmpRect {(int)(this->coords.getX() - this->width/2), (int)(this->coords.getY() - this->height/2),
						(int)(this->coords.getX() + this->width/2), (int)(this->coords.getY() + this->height/2)  };
	return tmpRect;
}