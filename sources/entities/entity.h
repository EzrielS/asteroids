#ifndef __ENTITY_H__
#define __ENTITY_H__

class Entity
{
    private:
        double _x;
        double _y;
        double width;
        double height;
        SDL_Rect hitBox;

        Point coords;

        SDL_Renderer* renderer;

    public:
        SDL_Texture* image;
        SDL_Surface* imageAsSurf;
        double angle;
        Vec2d vitesse;

    	
        Entity(double x, double y, double width, double height, const char*  imageFile, SDL_Renderer* renderer);

        void update();
        void draw();
        SDL_Rect getRect();


};

#endif