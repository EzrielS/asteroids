#include "./entity.h"
#include "../../headers/vec2.h"

Entity::Entity(double x, double y, SDL_Surface* imageAsSurf, SDL_Renderer* renderer){
	this->renderer = renderer;	
	this->image = SDL_CreateTextureFromSurface(renderer,imageAsSurf);
	this->coords = Point(x, y);
	this->angle=0.;
	this->vitesse=Vec2d(0, 0);
	this->inertie = 1;
}

void Entity::update(){
	std::cout << "[UNITE UPDATED] w vitesse " << this->vitesse << " @ " << this->coords  << std::endl;
	this->coords = this->coords + this->vitesse;
	this->vitesse = this->vitesse * this->inertie;
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
}


void Entity::draw(){
	SDL_Rect tmpRect = this->getRect();
	SDL_RenderCopyEx(this->renderer,
                    this->image,
                    NULL,
                    &tmpRect,
                    this->angle,
                    NULL,			// center
                    SDL_FLIP_NONE);
}

double Entity::getAngle(){
	return this->angle;
}

void Entity::pivot(double angle){
	this->angle += angle;
}

Vec2d Entity::getVitesse(){
	return this->vitesse;
}

void Entity::setVitesse(Vec2d vit){
	this->vitesse = vit;
}

void Entity::setInertie(double inertie){
	this->inertie = inertie;
}


void Entity::addVitesse(Vec2d vit){
	this->vitesse = this->vitesse + vit;
}

SDL_Rect Entity::getRect(){
	SDL_Rect tmpRect;
	tmpRect.x = this->coords.getY();
	tmpRect.y = this->coords.getX();
	SDL_QueryTexture(this->image, NULL, NULL, &tmpRect.w, &tmpRect.h);
	return tmpRect;
}

