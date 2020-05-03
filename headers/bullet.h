#ifndef __BULLET_H__
#define __BULLET_H__

#include "../sources/entities/entity.h"

class Ship;

/**
 * Classe représentant un Missile
 * Elle hérite de la classe Entity
 */
class Bullet : public Entity
{
	private:
		int _damage; // Les dégats du missile
		Ship* _parent; // La vaisseau qui a tiré ce missile

	public:
		/**
		 * Constructeur d'une Bullet
		 * @param x position x de la bullet
		 * @param y position y de la bullet
		 * @param _asteroidsAsSurface surfaces de la bullet
		 * @param renderer renderer de la bullet
		 * @return La bullet créée
		 */
		Bullet(double x, double y, SDL_Surface* imageAsSurf, SDL_Renderer* renderer, int damage, int health, Ship* parent);

		/**
		 * Destructeur de la balle
		 */
		~Bullet();

		/**
		 * Permet de récupérer les dégats de la balle
		 * @return Les degats de la balle
		 */
		int getDamage();

		/**
		 * Permet de récupérer le vaisseau qui a tiré cette balle
		 * @return Un Ship
		 */
		Ship* getParent();

		/**
		 * Fonction d'update de la balle
		 * Elle calcul la nouvelle position de la balle
		 */
		void update();
}; 

#endif