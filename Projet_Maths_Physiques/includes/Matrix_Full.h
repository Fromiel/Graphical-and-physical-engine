#ifndef MATRIX_FULL_H
#define MATRIX_FULL_H

#include <vector>
#include <ostream>

/**
 * @brief Classe représentant des matrices
 */
class Matrix_Full
{
    private: 
        /*tableau de double où l'on stocke les éléments de la matrice*/
        double * data_;
        /**nombre de lignes de la matrice*/
        int nl_;
        /**nombre de colonnes de la matrice*/
        int nc_;

    public:
        /**
         * @brief Constructeur de Matrix_Full avec les attributs à initialiser
         * 
         * @param nl nombre de lignes
         * @param nc nombre de colonnes
         */
        Matrix_Full(int nl, int nc);

        /**
         * @brief Constructeur de copie de Matrix_Full
         * 
         * @param m 
         */
        Matrix_Full(const Matrix_Full & m);
        /**
         * @brief Destructeur de Matrix_Full
         * 
         */
        ~Matrix_Full();

        /**
         * @brief Obtenir le nombre de lignes de la matrice
         * 
         * @return int 
         */
        int get_nl() const {return nl_;}

        /**
         * @brief Obtenir le nombre de colonnes de la matrice
         * 
         * @return int 
         */
        int get_nc() const {return nc_;}

        /**
         * @brief operator= de Matrix_Full
         * 
         * @param m 
         * @return Matrix_Full& 
         */
        Matrix_Full & operator=(const Matrix_Full m);

        /**
         * @brief renvoie l'élément à la ligne l et la colonne c
         * 
         * @param l 
         * @param c 
         * @return double 
         */
        double operator()(int l, int c) const;

        /**
         * @brief renvoie l'élément à la ligne l et la colonne c
         * 
         * @param l 
         * @param c 
         * @return double 
         */
        double & operator()(int l, int c);

        /**
         * @brief operator+= pour Matrix_Full
         * 
         * @param m 
         * @return Matrix_Full& 
         */
        Matrix_Full & operator+=(const Matrix_Full & m);

        /**
         * @brief operator-= pour Matrix_Full
         * 
         * @param m 
         * @return Matrix_Full& 
         */
        Matrix_Full & operator-=(const Matrix_Full & m);

        /**
         * @brief calcule la tansposée de la matrice
         * 
         * @return Matrix_Full 
         */
        Matrix_Full transp() const;

    /**
     * @brief retourne la matrice de rotation d'une rotation d'angle theta selon l'axe x (en coordonnées homogènes)
     * 
     * @param theta angle de rotation
     * @return Matrix_Full matrice de rotation
     */
    static Matrix_Full rotation_matrix_x(float theta);

    /**
     * @brief retourne la matrice de rotation d'une rotation d'angle theta selon l'axe y (en coordonnées homogènes)
     * 
     * @param theta angle de rotation
     * @return Matrix_Full matrice de rotation
     */
    static Matrix_Full rotation_matrix_y(float theta);

    /**
     * @brief retourne la matrice de rotation d'une rotation d'angle theta selon l'axe z (en coordonnées homogènes)
     * 
     * @param theta angle de rotation
     * @return Matrix_Full matrice de rotation
     */
    static Matrix_Full rotation_matrix_z(float theta);

    /**
     * @brief Obtenir la matrice de translation par une translation (x, y, z) en coordonnées homogènes
     * 
     * @param x 
     * @param y 
     * @param z 
     * @return Matrix_Full matrice de translation
     */
    static Matrix_Full get_translation_matrix(float x, float y, float z);

    /**
     * @brief retourne la matrice identité de taille i
     * 
     * @param i 
     * @return Matrix_Full 
     */
    static Matrix_Full identity(int i);

    /**matrice identité de taille 4*/
    const static Matrix_Full id4;

};

/**
 * @brief permet d'afficher une matrice
 * 
 * @param out 
 * @param v 
 * @return std::ostream& 
 */
std::ostream & operator<<(std::ostream & out, const Matrix_Full & v);

/**
 * @brief operator+ entre deux Matrix_Full
 * 
 * @param m1 
 * @param m2 
 * @return Matrix_Full 
 */
Matrix_Full operator+(const Matrix_Full m1, const Matrix_Full m2);

/**
 * @brief operator- entre deux Matrix_Full
 * 
 * @param m1 
 * @param m2 
 * @return Matrix_Full 
 */
Matrix_Full operator-(const Matrix_Full m1, const Matrix_Full m2);

/**
 * @brief operator* entre deux Matrix_Full
 * 
 * @param m1 
 * @param m2 
 * @return Matrix_Full 
 */
Matrix_Full operator*(const Matrix_Full m1, const Matrix_Full m2);

/**
 * @brief operator* entre une Matrix_Full et un vecteur colonne
 * 
 * @param m1
 * @param vect vecteur colonne
 * @return Matrix_Full 
 */
Matrix_Full operator*(const Matrix_Full m, std::vector<double> & vect);

/**
 * @brief operator* entre une Matrix_Full et un vecteur ligne
 * 
 * @param vect vecteur ligne
 * @param m
 * @return Matrix_Full 
 */
Matrix_Full operator*(std::vector<double> & vect, const Matrix_Full m);


#endif