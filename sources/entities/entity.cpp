#include "./entity.h"

Entity::Entity(double x, double y, SDL_Surface* imageAsSurf, SDL_Renderer* renderer){
	this->_renderer = renderer;	
	this->_image = SDL_CreateTextureFromSurface(renderer,imageAsSurf);
	this->_coords = Point(x, y);
	this->_angle = 0.;
	this->_vitesse = Vec2d(0, 0);
	this->_inertie = 1;
}
Entity::Entity(Point coords, SDL_Surface* imageAsSurf, SDL_Renderer* renderer){
	this->_renderer = renderer;	
	this->_image = SDL_CreateTextureFromSurface(renderer,imageAsSurf);
	this->_coords = coords;
	this->_angle=0.;
	this->_vitesse=Vec2d(0, 0);
	this->_inertie = 1;
}

Entity::~Entity() { }


void Entity::update(){
	this->_coords = this->_coords + this->_vitesse;
	this->_vitesse = this->_vitesse * this->_inertie;

	if(this->_coords.getY() > 1030){
		this->_coords.setY(-29);
	}

	if(this->_coords.getY() < -30){
		this->_coords.setY(1029);
	}

	if(this->_coords.getX() > 630){
		this->_coords.setX(-29);
	}

	if(this->_coords.getX() < -30){
		this->_coords.setX(629);
	}
}


void Entity::draw(){
	SDL_Rect tmpRect = this->getRect();
	SDL_RenderCopyEx(this->_renderer,
                    this->_image,
                    NULL,
                    &tmpRect,
                    this->_angle,
                    NULL,			// center
                    SDL_FLIP_NONE);
}

void Entity::gotHit(int d) {
	this->_health -= d;
}

double Entity::getAngle(){
	return this->_angle;
}

void Entity::pivot(double angle){
	this->_angle += angle;
}

Vec2d Entity::getVitesse(){
	return this->_vitesse;
}

void Entity::setVitesse(Vec2d vit){
	this->_vitesse = vit;
}

void Entity::setInertie(double inertie){
	this->_inertie = inertie;
}

void Entity::speedUp(Vec2d vit){
	this->_vitesse = this->_vitesse + vit;
}

void Entity::slowDown(Vec2d vit){
	this->_vitesse = this->_vitesse - vit;
}

Point Entity::getCoords(){
	return this->_coords;
}

int Entity::getHealth() {
	return _health;
}

int Entity::getDamage() {
	return _damage;
}

SDL_Rect Entity::getRect(){
	SDL_Rect tmpRect;
	tmpRect.x = this->_coords.getY();
	tmpRect.y = this->_coords.getX();
	SDL_QueryTexture(this->_image, NULL, NULL, &tmpRect.w, &tmpRect.h);
	tmpRect.x -= tmpRect.w/2;
	tmpRect.y -= tmpRect.h/2;
	return tmpRect;
}

SDL_Renderer* Entity::getRenderer(){
	return this->_renderer;
}