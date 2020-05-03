#ifndef __GAME_H__
#define __GAME_H__

#include <list>

/**
 * Classe représentant le Game Manager
 */
class Game
{
    public:
        SDL_Renderer* _renderer; // Le renderer de la Game
        std::list<Entity*> entities; // La liste des entités de la game

    private:
        Game(); // Constructeur privé de la classe
        ~Game(); // Constructeur privé de la classe
        static Game _instance; // Instance unique et privée de la classe

    public:
        /**
         * On supprime le constructeur par copie
         */
        Game(Game const&) = delete;

        /**
         * On supprime le constructeur par affectation
         */
        Game& operator=(Game const&) = delete;

        /**
         * Fonction qui permet de récupérer l'unique instance de la classe Game
         * @return L'unique instance de la classe Game
         */
        static Game& getInstance();

        /**
         * Fonction qui permet d'ajouter une entité au jeu
         * @param e L'entité à ajouter
         */
        static void addEntity(Entity *e);

        /**
         * S'occupe de mettre à jour toutes les entités à l'écran
         */
        void update();

        /**
         * S'occupe de dessiner toutes les entités à l'écran
         */
        void draw();

        /**
         * Fonction qui permet d'initialiser une partie
         * @param renderer Le renderer de la partie
         */
        void init(SDL_Renderer* renderer);

        /**
         * Fonction qui permet de terminer une partie
         */
        static void end();
};

#endif