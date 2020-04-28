#ifndef __ASTEROID_H__
#define __ASTEROID_H__

class Asteroid : public Entity
{
	private:
		int _damage;
		std::list<SDL_Surface*> _asteroidsAsSurface;

	public:
		Asteroid(double x, double y,  std::list<SDL_Surface*> _asteroidsAsSurface, SDL_Renderer* renderer);
		Asteroid(Point coords, std::list<SDL_Surface*> _asteroidsAsSurface, SDL_Renderer* renderer);

		~Asteroid();
		
		void update();
};

#endif