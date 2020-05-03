#ifndef __ASTEROID_H__
#define __ASTEROID_H__

/**
 * Classe représentant un Asteroid
 * Elle hérite de la classe Entity
 */
class Asteroid : public Entity
{
	private:
		int _damage; // Les dégats de l'asteroid
		std::list<SDL_Surface*> _asteroidsAsSurface; // La surface de l'asteroid

	public:
		/**
		 * Constructeur de l'asteroid
		 * @param x position x de l'asteroid
		 * @param y position y de l'asteroid
		 * @param _asteroidsAsSurface surfaces de l'asteroid
		 * @param renderer renderer de l'asteroid
		 * @return L'asteroid créé
		 */
		Asteroid(double x, double y,  std::list<SDL_Surface*> _asteroidsAsSurface, SDL_Renderer* renderer);

		/**
		 * Constructeur de l'asteroid
		 * @param coords position de l'asteroid
		 * @param _asteroidsAsSurface surfaces de l'asteroid
		 * @param renderer renderer de l'asteroid
		 * @return L'asteroid créé
		 */
		Asteroid(Point coords, std::list<SDL_Surface*> _asteroidsAsSurface, SDL_Renderer* renderer);

		/**
		 * Destructeur de l'asteroid
		 * Elle s'occupe de diviser les asteroids
		 */
		~Asteroid();
		
		/**
		 * Fonction d'update de l'asteroid
		 * Elle calcul la nouvelle position de l'asteroid
		 */
		void update();
};

#endif