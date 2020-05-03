#ifndef __WEAPON_H__
#define __WEAPON_H__

class Ship;

#include "../headers/game.h"

/**
 * Classe représentant l'Arme d'un Vaisseau
 */
class Weapon
{
    private:
		int _lastUsed; // Dernière arme utilisée
		int _damage; // Les dégats de l'arme
		SDL_Surface* _imageAsSurf; // La surface de l'arme
		double _vitesse; // La vitesse des balles de l'arme
		int _cooldown; // La vitesse de tire de l'arme
		int _bulletHealth; // Le temps de vie d'une balle
		Ship* _ship; // Le vaisseau qui possède cette arme
		int _currentCooldown = 0; // Valeur interne pour détruire les balles

	public:
		/**
		 * Constructeur d'une Bullet
		 * @param x position x de la bullet
		 * @param y position y de la bullet
		 * @param _asteroidsAsSurface surfaces de la bullet
		 * @param renderer renderer de la bullet
		 * @return La bullet créée
		 */
		Weapon(SDL_Surface* imageAsSurf, int damage, double vitesse, int cooldown, int bulletHealth);

		/**
		 * Getter de la vitesse de l'arme
		 * @return la vitesse de cette arme
		 */
		double getVitesse();

		/**
		 * Setter de la vitesse de l'arme
		 * @param v la nouvelle vitesse de l'arme
		 */
		void setVitesse(double v);

		/**
		 * Méthode qui permet de tirer une balle
		 */
		void fire();

		/**
		 * Méthode qui permet d'associer une arme à un vaisseau
		 * @param ship Le vaisseau qui possède l'arme
		 */
		void bind(Ship* ship);

		/**
		 * Fonction d'update de l'arme
		 * Elle calcul le cooldown de l'arme
		 */
		void update();
};

#endif