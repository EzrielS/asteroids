#ifndef __SHIP_H__
#define __SHIP_H__

#include "../sources/bullet.cpp"
#include "weapon.h"

/**
 * Classe représentant un Vaisseau
 * Elle hérite de la classe Entity
 */
class Ship : public Entity {
    public:
        bool shipInvincible = false; // les vaisseau est-il invincible ?
    private:
        int _nbVie; // Le nombre de vies du vaisseau (i.e. le joueur)
        int _score; // Le score du vaisseau (i.e. le joueur)
        std::list<Weapon*> _weapons; // Les armes du vaisseau
        std::list<Bullet*> _bullets; // Les balles du vaisseau

    public:
        /**
         * Constructeur d'un Ship
         * @param x position x d'un Ship
         * @param y position y d'un Ship
         * @param imageAsSurf surfaces d'un Ship
         * @param renderer renderer d'un Ship
         * @param nbVie le nombre de point de vies d'un Ship (i.e. du joueur)
         * @return Le Ship créé
         */
        Ship(double x, double y, SDL_Surface* imageAsSurf, SDL_Renderer* renderer, int nbVie);

        /**
         * Getter de la liste des balles du Ship
         * @return Les Balles du vaisseau
         */
        std::list<Bullet*> getBullets();
        /**
         * Getter de la liste des armes du Ship
         * @return Les armes du vaisseau
         */
        std::list<Weapon*> getWeapons();
        /**
         * Getter de la vie du Ship
         * @return la vie du vaisseau
         */
        int getVie();
        /**
         * Setter de la vie du Ship
         * @param v la nouvelle vie du vaisseau
         */
        void setVie(int v);
        /**
         * Getter du score du Ship (i.e. du joueur)
         * @return le score du vaisseau (i.e. du joueur)
         */
        int getScore();
 //       std::list<Weapon*> getWeapons();

        /**
         * Ajout de points dans le score
         * @param nb le nombre de points à ajouter au score
         */
        void addScore(int nb);

        /**
         * Permet de donner une arme au vaisseau
         * @param w l'arme à ajouter au vaisseau
         */
        void giveWeapon(Weapon* w);

        /**
         * Méthode pour mettre à jour un vaisseau
         */
        virtual void update();
        
        /**
         * Méthode pour dessiner un vaisseau
         */
        virtual void draw();
};

#endif
