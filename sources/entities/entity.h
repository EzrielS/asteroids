#ifndef __ENTITY_H__
#define __ENTITY_H__

class Entity
{
    protected:
        SDL_Texture* _image;
        SDL_Rect _hitBox;

        Point _coords;

        SDL_Renderer* _renderer;
        double _angle;
        Vec2d _vitesse;
        double _inertie;
        int _health = 100;
        int _damage = 100;


    public:
        virtual ~Entity();

        Entity(double x, double y,  SDL_Surface* imageAsSurf, SDL_Renderer* renderer);
        Entity(Point coords, SDL_Surface* imageAsSurf, SDL_Renderer* renderer);
        
        double getAngle();
        Vec2d getVitesse();

        int getHealth();
        int getDamage();

        void gotHit(int d);

        void setVitesse(Vec2d vit);
        void speedUp(Vec2d vit);
        void slowDown(Vec2d vit);
        void pivot(double angle);

        SDL_Renderer* getRenderer();

        void setInertie(double inertie);
        virtual void update();
        virtual void draw();
        SDL_Rect getRect();

        Point getCoords();
};

#endif