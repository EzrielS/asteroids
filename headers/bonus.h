#ifndef __BONUS_H__
#define __BONUS_H__

#include "point.h"

/**
 * Classe représentant un Bonus
 */
class Bonus
{
	private:
		SDL_Texture* _image;
		SDL_Rect _hitBox;
		Point _coords;
		SDL_Renderer* _renderer;

	public:
		/**
		 * Constructeur du Bonus
		 * @param x position x du bonus
		 * @param y position y du bonus
		 * @param _asteroidsAsSurface surfaces du bonus
		 * @param renderer renderer du bonus
		 * @return Le Bonus créé
		 */
        Bonus(double x, double y,  SDL_Surface* imageAsSurf, SDL_Renderer* renderer);

		/**
		 * Constructeur du Bonus
		 * @param coords position du bonus
		 * @param _asteroidsAsSurface surfaces du bonus
		 * @param renderer renderer du bonus
		 * @return Le Bonus créé
		 */
        Bonus(Point coords, SDL_Surface* imageAsSurf, SDL_Renderer* renderer);

		/**
		 * Destructeur du bonus
		 * Il s'occupe de l'effacer de l'écran
		 */
		~Bonus();

		/**
		 * S'occupe de faire l'effet du Bonus
		 */
        void doBonus();

		/**
		 * S'occupe de dessiner le Bonus à l'écran
		 */
        void draw();

		/**
		 * Permet de récupérer la hitbox du Bonus
		 * @return La hitbox du Bonus
		 */
        SDL_Rect getRect();
};

#endif