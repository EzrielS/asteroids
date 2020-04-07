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
        int _health = 100;


    public:

    	
        Entity(double x, double y,  SDL_Surface* imageAsSurf, SDL_Renderer* renderer);
        Entity(Point coords, SDL_Surface* imageAsSurf, SDL_Renderer* renderer);
        
        double getAngle();
        Vec2d getVitesse();

        int getHealth();

        void setVitesse(Vec2d vit);
        void addVitesse(Vec2d vit);
        void pivot(double angle);
        
        SDL_Renderer* getRenderer();

        void setInertie(double inertie);
        virtual void update();
        virtual void draw();
//        Point getCenter();
        SDL_Rect getRect();

        Point getCoords();


};

#endif