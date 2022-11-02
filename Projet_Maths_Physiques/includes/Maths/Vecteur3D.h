//
// Created by jules on 07/09/2022.
//

#ifndef VECTEUR3D_H
#define VECTEUR3D_H

#include <iostream>
#include <cmath>

class Vecteur3D{

    private :
        float _x;
        float _y;
        float _z;

    public:

        /// <summary>
        /// Constructeur valu�, renvoyant par d�faut le vecteur nul
        /// </summary>
        /// <param name="x"> Premi�re composante du vecteur </param>
        /// <param name="y"> Seconde composante du vecteur </param>
        /// <param name="z"> Troisi�me composante du vecteur </param>
        Vecteur3D(float x=0, float y=0, float z=0);

        /// <summary>
        /// Constructeur de copie de Vecteur3D
        /// </summary>
        /// <param name="vect"> Le vecteur dont on souhaite faire une copie </param>
        Vecteur3D(const Vecteur3D & vect);

        /// <summary>
        /// Getter de la premi�re composante du vecteur
        /// </summary>
        /// <returns> La valeur de la premi�re composante du vecteur </returns>
        float get_x() const {return _x;}

        /// <summary>
        /// Getter de la seconde composante du vecteur
        /// </summary>
        /// <returns> La valeur de la seconde composante du vecteur </returns>
        float get_y() const {return _y;}

        /// <summary>
        /// Getter de la derni�re composante du vecteur
        /// </summary>
        /// <returns> La valeur de la derni�re composante du vecteur </returns>
        float get_z() const {return _z;}

        /// <summary>
        /// Calcule la norme du vecteur
        /// </summary>
        /// <returns> Retourne la norme du vecteur </returns>
        float norm();

        /// <summary>
        /// Calcule la norme au carr� du vecteur
        /// </summary>
        /// <returns> Retourne la norme au carr� du vecteur </returns>
        float norm_squared();

        /// <summary>
        /// Normalise le vecteur
        /// </summary>
        /// <returns> Retourne le vecteur normalis� </returns>
        Vecteur3D normalized();

        /// <summary>
        /// Multiplication d'un vecteur par un scalaire
        /// </summary>
        /// <param name="scalar"> Le scalaire par lequel on souhaite multiplier le vecteur </param>
        /// <returns> Le r�sultat de la multiplication du scalaire avec le vecteur </returns>
        Vecteur3D scalar_multiplication(float scalar);

};

/// <summary>
/// M�thode permettant l'affichage d'un vecteur 
/// </summary>
/// <param name="out"> Flux sur lequel on souhaite afficher notre vecteur </param>
/// <param name="vect"> Le vecteur � afficher </param>
/// <returns> L'affichage du vecteur suur le flux pr�cis� </returns>
std::ostream & operator<<(std::ostream & out, const Vecteur3D & vect);

/// <summary>
/// Surcharge de l'op�rateur + 
/// </summary>
/// <param name="vect1"> Premier vecteur � additionner </param>
/// <param name="vect2"> Second vecteur � additionner </param>
/// <returns> La somme des deux vecteurs </returns>
Vecteur3D operator+(const Vecteur3D &vect1, const Vecteur3D &vect2);

/// <summary>
/// Surcharge de l'op�rateur -
/// </summary>
/// <param name="vect1"> Premier vecteur � soustraire</param>
/// <param name="vect2"> Second vecteur � soustraire </param>
/// <returns> La diff�rence des deux vecteurs </returns>
Vecteur3D operator-(const Vecteur3D &vect1, const Vecteur3D &vect2);

/// <summary>
/// Surcharge de l'op�rateur *
/// </summary>
/// <param name="vect1"> Premier vecteur � multiplier </param>
/// <param name="vect2"> Second vecteur � multiplier </param>
/// <returns> Le r�sultat de la multiplication terme � terme des deux vecteurs </returns>
Vecteur3D operator*(const Vecteur3D &vect1, const Vecteur3D &vect2);

/// <summary>
/// Surcharge de l'op�rateur *
/// </summary>
/// <param name="d"> Scalaire par lequel on veut multiplier le vecteur </param>
/// <param name="v"> Vecteur que l'on souhaite multiplier </param>
/// <returns> Le vecteur r�sultat de la multiplication </returns>
Vecteur3D operator*(const float d, const Vecteur3D& v);

/// <summary>
/// Surcharge de l'op�rateur *
/// </summary>
/// <param name="v"> Vecteur que l'on souhaite multiplier </param>
/// <param name="d">Scalaire par lequel on veut multiplier le vecteur </param>
/// <returns> Le vecteur r�sultat de la multiplication </returns>
Vecteur3D operator*(const Vecteur3D& v, const float d);

/// <summary>
/// Calcul du produit scalaire
/// </summary>
/// <param name="vect1"> Premier vecteur </param>
/// <param name="vect2"> Deuxi�me vecteur </param>
/// <returns> Le produit scalaire des deux vecteurs </returns>
float scalar_product(const Vecteur3D &vect1, const Vecteur3D &vect2);

/// <summary>
/// Calcul du produit vectoriel 
/// </summary>
/// <param name="vect1"> Premier vecteur </param>
/// <param name="vect2"> Deuxi�me vecteur </param>
/// <returns> Le produit vectoriel des deux vecteurs </returns>
Vecteur3D vectorial_product(const Vecteur3D &vect1, const Vecteur3D &vect2);

float distance(const Vecteur3D& vect1, const Vecteur3D& vect2);

#endif //VECTEUR3D_H
