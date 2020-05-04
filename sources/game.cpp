#include "../headers/game.h"
#include "print_string.cpp"

Game Game::_instance = Game();

Game::Game() { }

Game::~Game() { }

Game& Game::getInstance() {
    return _instance;
}

void Game::init(SDL_Renderer* renderer) {
	_renderer = renderer;
}

void Game::addEntity(Entity *e) {
	Game::getInstance().entities.push_front(e);
}

void Game::update(){
	for (std::list<Entity*>::iterator it=this->entities.begin(); it != this->entities.end(); ++it) {
		(*it)->update();
	}
}
void removeInvincibilityAfter2Seconds(bool& b) {
	std::this_thread::sleep_for (std::chrono::seconds(2));
	b = false;
}
bool checkCollisions(SDL_Rect A, SDL_Rect B);
void Game::collisions(){
	Game& g = Game::getInstance();
	int asteroidsCount = 0;
	for (std::list<Entity*>::iterator it=g.entities.begin(); it != g.entities.end(); ++it) { // Pour chaque entité
		if (dynamic_cast<Asteroid*>(*it) != 0) { // Pour chaque asteroid
			asteroidsCount++;
			Asteroid* tempAsteroid = dynamic_cast<Asteroid*>(*it);
			for (std::list<Entity*>::iterator it2=g.entities.begin(); it2 != g.entities.end(); ) { // On le compare avec les autres entités

				bool bRemoved = false;

				if(it != it2) { // On vérifie que ce n'est pas lui-même
					if (dynamic_cast<Ship*>(*it2) != 0) { 			// Si l'entité est un vaisseau
						Ship* tempShip = dynamic_cast<Ship*>(*it2);
						if(tempShip->getVie() <= 0) {
								g.draw();
								g.end();
								g.quit = true;
								print_str("You have lost", Point(375,250));
								print_str("Closing in 10 seconds...", Point(300,300));
						}
						if(!tempShip->shipInvincible && checkCollisions( tempAsteroid->getRect(), tempShip->getRect() )) {  // S'il touche un vaisseau
								tempShip->setVie(tempShip->getVie() - 1); // Le vaisseau perd 1 point de vie
								// Le vaisseau est invincible pndant 2 secondes après être touché.
								// Un thread s'occupe de modifier le booléen après 2 secondes pour ne pas bloquer le jeu.
								tempShip->shipInvincible = true;
								
								std::thread t1(removeInvincibilityAfter2Seconds, std::ref(tempShip->shipInvincible));
								t1.detach();
						}
					} else if (dynamic_cast<Bullet*>(*it2) != 0) { 		// Si l'entité est une balle
						Bullet* tempBullet = dynamic_cast<Bullet*>(*it2);
						if(checkCollisions( tempAsteroid->getRect(), tempBullet->getRect() )) {  // S'il touche une bullet
							tempAsteroid->gotHit(tempBullet->getDamage()); // L'asteroid prend les dégats de la balle
							tempBullet->getParent()->addScore(1);
							(*it2)->~Entity();
							it2 = g.entities.erase(it2);
							bRemoved = true;
						}
					}
				}
				if(!bRemoved){
					++it2;
				}
			}
					
		} else if(dynamic_cast<Ship*>(*it) != 0) {  // Pour chaque vaisseau
			Ship* tempShip = dynamic_cast<Ship*>(*it);
			auto bon_it=g.bonuses.begin();
			while(bon_it != g.bonuses.end()){
				Bonus* tmpBonus = *bon_it;
				if(checkCollisions( tempShip->getRect(), tmpBonus->getRect())){
					double vitesse = tempShip->getWeapons().front()->getVitesse();
					tempShip->getWeapons().front()->setVitesse(vitesse*2);
					delete tmpBonus;
					bon_it = g.bonuses.erase(bon_it);
				}
				else{
					bon_it++;
				}
			}
		}
		if((*it)->getHealth() <= 0) { // Si l'entité n'a plus de vie, on l'a supprime
			(*it)->~Entity();
			g.entities.erase(it--);
		}
	}
	// S'il ne reste plus aucun asteroid alors un nouveau apparaît
	if(asteroidsCount == 0) {
		Asteroid *newAsteroid = new Asteroid(rand()%600, rand()%1000, std::list<SDL_Surface*> { getImageAsSurface("images/asteroide1.bmp"),
			getImageAsSurface("images/asteroide2.bmp"), getImageAsSurface("images/asteroide3.bmp") }, g._renderer);
		g.entities.push_front(newAsteroid); // On ajoute l'asteroid dans la liste des entités
	}
}

void Game::draw(){
		// On dessine les bonus
	for (std::list<Bonus*>::iterator it=this->bonuses.begin(); it != this->bonuses.end(); ++it) {
		(*it)->draw();
	}

	for (std::list<Entity*>::iterator it=this->entities.begin(); it != this->entities.end(); ++it) {
		(*it)->draw();
	}
}

void Game::end() {
	Game& g = Game::getInstance();

	for (std::list<Entity*>::iterator it=g.entities.begin(); it != g.entities.end(); ++it) {
		(*it)->setVitesse(Vec2d(0.,0.));
	}
}

bool checkCollisions(SDL_Rect A, SDL_Rect B) {
	//Les côtés des rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
 
    //Calcul les côtés du rectangle A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
 
    //Calcul les côtés du rectangle B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

	//Tests de collisions
    if( bottomA <= topB ) {
        return false;
    }
 
    if( topA >= bottomB ) {
        return false;
    }
 
    if( rightA <= leftB ) {
        return false;
    }
 
    if( leftA >= rightB ) {
        return false;
    }
 
    //Si collision détectée
    return true;
}
