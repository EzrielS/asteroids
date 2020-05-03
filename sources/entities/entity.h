#ifndef __ENTITY_H__
#define __ENTITY_H__

/**
 * Classe représentant une Entité du jeu
 */
class Entity
{
    protected:
        SDL_Texture* _image; // L'image affichée pour l'entité
        SDL_Rect _hitBox;    // La hitbox de l'entité

        Point _coords;       // Les coordonnées de l'entité

        SDL_Renderer* _renderer; // Le renderer de l'entité
        double _angle;           // L'angle de déplacement
        Vec2d _vitesse;          // La vitesse de déplacement
        double _inertie;         // L'inertie
        int _health = 100;       // Les points de vie de l'entité
        int _damage = 100;       // Les dommages effectués par cette entité


    public:
        /**
         * Constructeur d'une Entity
         * @param x position x de l'Entity
         * @param y position y de l'Entity
         * @param imageAsSurf surfaces de l'Entity
         * @param renderer renderer de l'Entity
         * @return L'Entity créé
         */
        Entity(double x, double y,  SDL_Surface* imageAsSurf, SDL_Renderer* renderer);

        /**
         * Constructeur d'une Entity
         * @param x position x de l'Entity
         * @param y position y de l'Entity
         * @param imageAsSurf surfaces de l'Entity
         * @param renderer renderer de l'Entity
         * @return L'Entity créé
         */
        Entity(Point coords, SDL_Surface* imageAsSurf, SDL_Renderer* renderer);

        /**
         * Destructeur virtual des entity
         * Permet d'appeler celui des classes filles
         */
        virtual ~Entity();


        /**
         * Getter de l'angle de l'entité
         * @return l'angle de l'entité
         */
        double getAngle();
        /**
         * Getter de la vitesse de l'entité
         * @return la vitesse de l'entité
         */
        Vec2d getVitesse();
        /**
         * Setter de la vitesse de l'entité
         * @param vit Nouvelle vitesse de l'entité
         */
        void setVitesse(Vec2d vit);
        /**
         * Getter de la vie de l'entité
         * @return la vie de l'entité
         */
        int getHealth();
        /**
         * Getter des dégats de l'entité
         * @return les dégats de l'entité
         */
        int getDamage();
        /**
         * Getter du renderer de l'entité
         * @return le renderer de l'entité
         */
        SDL_Renderer* getRenderer();
        /**
         * Getter des coordonnées de l'entité
         * @return les coordonnées de l'entité
         */
        Point getCoords();
        /**
         * Getter de la hitbox de l'entité
         * @return la hitbox de l'entité
         */
        SDL_Rect getRect();
        /**
         * Setter de l'inertie de l'entité
         * @param inertie Nouvelle inertie de l'entité
         */
        void setInertie(double inertie);

        /**
         * Méthode appelée quand l'entité est touchée
         * @param d les dégats pris par l'entité
         */
        void gotHit(int d);

        /**
         * Méthode pour augmenter la vitesse d'une entité
         * @param vit nouvelle vitesse de l'entité
         */
        void speedUp(Vec2d vit);
        /**
         * Méthode pour réduire la vitesse d'une entité
         * @param vit nouvelle vitesse de l'entité
         */
        void slowDown(Vec2d vit);
        /**
         * Méthode pour pivoter une entité
         * @param angle degré de rotation de l'entité
         */
        void pivot(double angle);

        /**
         * Méthode virtual pour mettre à jour une entité
         * Appelle la méthode de la classe fille correspondante
         */
        virtual void update();

        /**
         * Méthode virtual pour dessiner une entité
         * Appelle la méthode de la classe fille correspondante
         */
        virtual void draw();
};

#endif