/**
 * \file Matrice.h
 * \brief Interface des matrices carrées.
 *
 * Header du fichier Matrice.cpp. Définition de la classe Matrice, de ses membres, de ses constructeurs,
 * de ses opérateurs internes et externes, et d'autres fonctions.
 */

#ifndef _MATRICE_H
#define _MATRICE_H

#include <iostream>
#include "Point3D.h"
#include "Point2D.h"

/**
 * \class Matrice
 * \brief Création de la classe Matrice.
 *
 * Contient deux membres correspondant à la dimension de la matrice et à ses données.
 * Contient également d'autres fonctions permettant de réaliser les opérations de base sur les matrices.
 */
class Matrice {
private: /*!< La taille de la matrice et ses données */
    int n_;
    float *data_;

public:
    /**
     * \brief Constructeur valué / par défaut de la classe Matrice.
     * \param n Taille de la matrice.
     *
     * Construit une matrice à partir de la taille donnée en paramètre.
     */
    Matrice(int n = 3);

    /**
     * \brief Constructeur de copie de la classe Matrice.
     * \param mat Une référence de la matrice à copier.
     *
     * Construit une matrice qui aura les mêmes membres de classe que la matrice donnée en paramètre.
     */
    Matrice(const Matrice &mat);

    /**
     * \brief Destructeur de la classe Matrice.
     *
     * Supprime proprement les données de la matrice.
     */
    ~Matrice();

    /* Getters */

    /**
     * \brief Getters du membre n_.
     * \return La taille de la matrice carrée.
     */
    int get_n() const;

    /* Opérateurs internes */

    /**
     * \brief Opérateur interne () de la classe Matrice.
     * \param i Indice de la ligne.
     * \param j Indice de la colonne.
     * \return Une référence de la valeur située aux coordonnées (i,j) dans la matrice.
     */
    float & operator()(int i, int j);

    /**
     * \brief Opérateur interne () constant de la classe Matrice.
     * \param i Indice de la ligne.
     * \param j Indice de la colonne.
     * \return La valeur située aux coordonnées (i,j) dans la matrice.
     */
    float operator()(int i, int j) const;

    /**
     * \brief Opérateur interne = de la classe Matrice.
     * \param mat Une matrice (const) à affecter à la variable.
     * \return Une référence de la matrice dont la taille et les vaileurs ont pris les valeurs de celles de la matrice donnée en paramètre.
     */
    Matrice & operator=(const Matrice mat);

    /* Fonctions */

    /**
     * \brief Transposée d'une matrice.
     * \param mat Une matrice.
     * \return La transposée de la matrice donnée en paramètre.
     */
    Matrice transp(Matrice mat);
};

/* Opérateurs externes */

/**
 * \brief Opérateur externe de flux pour une matrice.
 * \param st Une réference du flux à utiliser.
 * \param mat Une réference de la matrice à afficher.
 * \return Un flux.
 */
std::ostream & operator<<(std::ostream & st, const Matrice &mat);

/**
 * \brief Opérateur externe + pour deux matrices.
 * \param mat1 Une matrice à additionner.
 * \param mat2 La deuxième matrice à additionner.
 * \return La somme des deux matrices.
 */
Matrice operator+(const Matrice & mat1, const Matrice & mat2);

/**
 * \brief Opérateur externe - pour deux matrices.
 * \param mat1 Une matrice.
 * \param mat2 La matrice à soustraire.
 * \return La différence des deux matrices.
 */
Matrice operator-(const Matrice & mat1, const Matrice & mat2);

/**
 * \brief Opérateur externe * pour deux matrices.
 * \param mat1 Une matrice.
 * \param mat2 La matrice à multiplier.
 * \return La multiplication des deux matrices.
 */
Matrice operator*(const Matrice & mat1, const Matrice & mat2);

/**
 * \brief Opérateur externe * pour une matrice et un scalaire.
 * \param mat Une matrice.
 * \param x Un scalaire.
 * \return La matrice multipliée par le scalaire.
 */
Matrice operator*(const Matrice & mat, float x);

/**
 * \brief Opérateur externe * pour une matrice et un scalaire.
 * \param x Un scalaire.
 * \param mat Une matrice.
 * \return La matrice multipliée par le scalaire.
 */
Matrice operator*(float x, const Matrice & mat);

/**
 * \brief Opérateur externe * pour une matrice et un Vecteur3D.
 * \param mat Une matrice.
 * \param p Un vecteur 3D.
 * \return Le vecteur multiplié la matrice.
 */
Vecteur3D operator*(const Matrice & mat, const Vecteur3D & p);

/**
 * \brief Opérateur externe * pour une matrice et un Vecteur2D.
 * \param mat Une matrice.
 * \param p Un vecteur 2D.
 * \return Le vecteur multiplié la matrice.
 */
Vecteur2D operator*(const Matrice & mat, const Vecteur2D & p);

/**
 * \brief Opérateur externe / pour une matrice et un scalaire.
 * \param mat Une matrice.
 * \param x Un scalaire non nul.
 * \return La matrice divisée par le scalaire.
 */
Matrice operator/(const Matrice & matrice, float x);

/* Fonctions */

/**
 * \brief Une fonction renvoyant la matrice de rotation associée à un axe et un angle.
 * \param p Un axe (Vecteur3D) non nul.
 * \param angle Un angle (en radian).
 * \return La matrice de rotation associée à l'axe et l'angle donnés en paramètre.
 */
Matrice Mat_Rotation(Vecteur3D p, float angle);

/**
 * \brief Une fonction calculant la matrice de projection associée à un FOV, et au champs de vision d'une caméra.
 * \param FOVx Le FOV selon l'axe X de la caméra.
 * \param FOVy Le FOV selon l'axe Y de la caméra.
 * \param Zmin La distance minimale à laquelle la caméra peut voir.
 * \param Zmax La distance maximale à laquelle la caméra peut voir.
 * \return La matrice de projection associée aux paramètres donnés.
 */
Matrice Mat_Projection(float FOVx, float FOVy, float Zmin, float Zmax);

#endif //_MATRICE_H
