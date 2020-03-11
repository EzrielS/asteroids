#include "../headers/ship.h"

Ship::Ship() : _speed(0.) { }

void Ship::draw(SDL_Renderer* renderer) {
    Point p1 = Point(500,300);
    Point p2 = Point(490,325);
    Point p3 = Point(510,325);

    SDL_RenderDrawLine(renderer, p1.getX(), p1.getY(), p2.getX(), p2.getY());
    SDL_RenderDrawLine(renderer, p1.getX(), p1.getY(), p3.getX(), p3.getY());
    SDL_RenderDrawLine(renderer, p2.getX(), p2.getY(), p3.getX(), p3.getY());
}