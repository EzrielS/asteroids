#ifndef __VEC2_H__
#define __VEC2_H__

#include <string>
#include <math.h>

/**
 * Classe template représentant un vecteur de taille 2
 * Elle permet de stocker tout objet en 2 exemplaires
 */
template <class T>
class Vec2
{
    public:
        T _x, _y; // Premier et Deuxième élément du vecteur

        /**
         * Constructeur vide par defaut
         */
        Vec2() : _x(0), _y(0) { };

        /**
         * Constructeur du vecteur
         * @param x premier élément
         * @param y deuxième élément
         */
        Vec2(T x, T y) : _x(x), _y(y) { };

        /**
         * Constructeur du vecteur par copie
         * @param x premier élément
         * @param y deuxième élément
         */
        Vec2(const Vec2& v) : _x(v._x), _y(v._y) { };

        /**
         * Setter du vecteur
         * @param x premier élément à modifier
         * @param y deuxième élément à modifier
         */
        void set(T x, T y) {
            this->_x = x;
            this->_y = y;
        }

        /**
         * Surcharge de l'opérateur +
         * @param v vecteur à additionner
         * @return Le nouveau vecteur
         */
        Vec2 operator+(Vec2& v) {
            return Vec2(_x + v._x, _y + v._y);
        }

        /**
         * Surcharge de l'opérateur -
         * @param v vecteur à soustraire
         * @return Le nouveau vecteur
         */
        Vec2 operator-(Vec2& v) {
            return Vec2(_x - v._x, _y - v._y);
        }

        /**
         * Surcharge de l'opérateur +=
         * @param v vecteur à additionner
         */
        Vec2& operator+=(Vec2& v) {
            _x += v._x;
            _y += v._y;
            return *this;
        }

        /**
         * Surcharge de l'opérateur -=
         * @param v vecteur à sustraire
         */
        Vec2& operator-=(Vec2& v) {
            _x -= v._x;
            _y -= v._y;
            return *this;
        }

        /**
         * Surcharge de l'opérateur + double
         * @param s valeur à additionner
         * @return Le nouveau vecteur
         */
        Vec2 operator+(double s) {
            return Vec2(_x + s, _y + s);
        }
        /**
         * Surcharge de l'opérateur - double
         * @param s valeur à additionner
         * @return Le nouveau vecteur
         */
        Vec2 operator-(double s) {
            return Vec2(_x - s, _y - s);
        }
        /**
         * Surcharge de l'opérateur * double
         * @param s valeur à additionner
         * @return Le nouveau vecteur
         */
        Vec2 operator*(double s) {
            return Vec2(_x * s, _y * s);
        }
        /**
         * Surcharge de l'opérateur / double
         * @param s valeur à additionner
         * @return Le nouveau vecteur
         */
        Vec2 operator/(double s) {
            return Vec2(_x / s, _y / s);
        }

        /**
         * Surcharge de l'opérateur +=
         * @param s double à additionner
         */
        Vec2& operator+=(double s) {
            _x += s;
            _y += s;
            return *this;
        }
        /**
         * Surcharge de l'opérateur -=
         * @param s double à additionner
         */
        Vec2& operator-=(double s) {
            _x -= s;
            _y -= s;
            return *this;
        }
        /**
         * Surcharge de l'opérateur *=
         * @param s double à additionner
         */
        Vec2& operator*=(double s) {
            _x *= s;
            _y *= s;
            return *this;
        }
        /**
         * Surcharge de l'opérateur /=
         * @param s double à additionner
         */
        Vec2& operator/=(double s) {
            _x /= s;
            _y /= s;
            return *this;
        }

        /**
         * Surcharge de l'opérateur ==, permet de comparer deux vecteurs
         * @param v1 le premier vecteur à comparer
         * @param v2 le deuxième vecteur à comparer
         * @return un booléen si les deux vecteurs sont égaux ou non
         */
        friend bool operator==(const Vec2& v1, const Vec2& v2) {
            return (v1._x == v2._x && v1._y == v2._y);
        }
        /**
         * Surcharge de l'opérateur !=, permet de comparer deux vecteurs
         * @param v1 le premier vecteur à comparer
         * @param v2 le deuxième vecteur à comparer
         * @return un booléen si les deux vecteurs sont égaux ou non
         */
        friend bool operator!=(const Vec2& v1, const Vec2& v2) {
            return !(v1 == v2);
        }

        /**
         * Surcharge de l'opérateur [], permet d'obtenir une valeur dans un vecteur
         * @param i index de l'élément à récupérer
         * @return L'élément à la position i dans le vecteur
         */
        T& operator[](int i) {
            assert(i<2);
            if(i == 0) {
                return _x;
            } else {
                return _y;
            }
        }

        /**
         * Surcharge de l'opérateur <<, permet d'afficher un vecteur
         * @param os le flux où afficher le vecteur
         * @param v le vecteur à afficher
         * @return un stream de sortie
         */
        friend std::ostream& operator<<(std::ostream& os, const Vec2& v) {
            os << "Vec2[" << v._x << ", " << v._y << "]";
            return os;
        }

        /**
         * Normalisation d'un vecteur
         * @param v le vecteur à normaliser
         * @return un nouveau vecteur normalisé
         */
        static Vec2 normalize(const Vec2& v) {
            double m = sqrt(pow(v._x,2) + pow(v._y,2));
            return Vec2(v._x/m, v._y/m);
        }

};

typedef Vec2<int> Vec2i; // vecteur d'integer
typedef Vec2<float> Vec2f; // vecteur de float
typedef Vec2<double> Vec2d; // vecteur de double

/**
 * Calcul un nouveau vecteur déplacé par un angle
 * @param angle l'angle pour bouger le vecteur
 * @return le nouveau vecteur
 */
Vec2d angleToVec(double angle){
	return Vec2d(sin(angle*(2*M_PI/360)), cos(angle*(2*M_PI/360)));
}


#endif
