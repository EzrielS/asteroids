#ifndef __ENTITY_H__
#define __ENTITY_H__

class Entity
{
    protected:
        SDL_Texture* image;
        SDL_Rect hitBox;

        Point coords;

        SDL_Renderer* renderer;
        double angle;
        Vec2d vitesse;
        double inertie;



    public:

    	
        Entity(double x, double y,  SDL_Surface* imageAsSurf, SDL_Renderer* renderer);

        double getAngle();
        Vec2d getVitesse();

        void setVitesse(Vec2d vit);
        void addVitesse(Vec2d vit);
        void pivot(double angle);
        
        void setInertie(double inertie);
        void update();
        void draw();
        SDL_Rect getRect();


};

#endif