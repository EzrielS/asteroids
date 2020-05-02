#ifndef __BONUS_H__
#define __BONUS_H__

//#include <string>

class Bonus
{
	private:
        SDL_Texture* _image;
        SDL_Rect _hitBox;

        //std::string _bonusName;
        Point _coords;

        SDL_Renderer* _renderer;

	public:
        Bonus(double x, double y,  SDL_Surface* imageAsSurf, SDL_Renderer* renderer);
        Bonus(Point coords, SDL_Surface* imageAsSurf, SDL_Renderer* renderer);

		~Bonus();

        void draw();

        SDL_Rect getRect();
};

#endif