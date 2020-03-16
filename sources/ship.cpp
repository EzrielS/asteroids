#include "../headers/ship.h"

Ship::Ship() : _speed(0.), _shipHead(500., 300.), direction(-1) { }

void Ship::draw(SDL_Renderer* renderer) {
    Point p1 = _shipHead;
    Point p2 = Point(_shipHead.getX() - 10, _shipHead.getY() + 25);
    Point p3 = Point(_shipHead.getX() + 10, _shipHead.getY() + 25);

    SDL_RenderDrawLine(renderer, p1.getX(), p1.getY(), p2.getX(), p2.getY());
    SDL_RenderDrawLine(renderer, p1.getX(), p1.getY(), p3.getX(), p3.getY());
    SDL_RenderDrawLine(renderer, p2.getX(), p2.getY(), p3.getX(), p3.getY());
}

void Ship::speedUp() {
    std::cout << "speedUp" << std::endl;
    this->_speed += 1;
}

void Ship::slowDown() {
    std::cout << "slowDown" << std::endl;
    if(this->_speed > 0.) {
        this->_speed -= 0.5;
    } else {
        this->_speed = 0.;
    }
}

void Ship::move() {
    std::cout << "[" << this->_shipHead.getX() << ", " << this->_shipHead.getY() << "]" << std::endl;
    double x = x;//this->_shipHead.getX() * this->_speed;
    double y = this->direction * this->_speed;
    this->_shipHead = this->_shipHead.translation(x, y);

    if(this->_shipHead.getY() < 0) {
        this->_shipHead.setY(this->_shipHead.getY() + 600);
    }

    if(this->_shipHead.getY() > 600) {
        this->_shipHead.setY(this->_shipHead.getY() -600);
    }
}