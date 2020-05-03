#ifndef __POINT_H__
#define __POINT_H__

#include "vec2.h"

/**
 * Classe représentant un point en 2D dans l'espace
 */
class Point 
{
    private:
        double _x; // Coordonnée x du Point
        double _y; // Coordonnée y du Point

    public:
        /**
         * Constructeur vide d'un Point
         * @return Un point de coordonnées (0,0)
         */
        Point();
        /**
         * Constructeur d'un Point
         * @return Un point de coordonnées (x,y)
         */
        Point(double x, double y);

        /**
		 * Getter de la coordonnée x du Point
		 * @return la coordonnée x
		 */
        double getX();
        /**
		 * Getter de la coordonnée y du Point
		 * @return la coordonnée y
		 */
        double getY();

        /**
		 * Setter de la coordonnée x du Point
		 * @param x la nouvelle coordonnée x du Point
		 */
        void setX(double x);
        /**
		 * Setter de la coordonnée y du Point
		 * @param y la nouvelle coordonnée y du Point
		 */
        void setY(double y);

        /**
         * Méthode de translation d'un Point
         * @param translateX Valeur de translation en X
         * @param translateY Valeur de translation en Y
         * @return le nouveau point translaté
         */
        Point translation(double translateX, double translateY);

        /**
         * Surcharge de l'opérateur + Vec2d
         * @param v le vecteur à additionner au point
         * @return Le nouveau point
         */
        inline Point operator+(Vec2d& v) {
            return Point(double(_x + v[0]), double(_y + v[1]));
        }

        /**
         * Surcharge de l'opérateur <<, permet d'afficher un Point
         * @param os le flux où afficher le vecteur
         * @param p le point à afficher
         * @return un stream de sortie
         */
        friend std::ostream& operator<<(std::ostream& os, const Point& p) {
            os << "Point[" << p._x << ", " << p._y << "]";
            return os;
        }
};

#endif