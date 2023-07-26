#ifndef MATRIX4D_H
#define MATRIX4D_H

#include <ostream>
#include <vector>
#include "Vecteur3D.h"

#include <algorithm>
#include <functional>
#include <cmath>

class Matrix4D {
private:
    std::vector<double> _content;

public:
    static const int lineCount = 4;
    static const int columnCount = 4;
    
    /// <summary>
    /// Constructeur non valué de Matrix4D, avec comme valeur par défaut la matrice nulle
    /// </summary>
    Matrix4D();

    /// <summary>
    /// Constructeur valué de Matrix4D
    /// </summary>
    /// <param name="content">Un vecteur représentant le contenu de la matrice</param>
    Matrix4D(const std::vector<double>& content);

    /// <summary>
    /// Constructeur de copie de Matrix4D
    /// </summary>
    /// <param name="matrix4D"> La matrice dont on veut copier le contenu </param>
    Matrix4D(const Matrix4D& matrix4D);

    /// <summary>
    /// Getter de _content
    /// </summary>
    /// <returns> Un vecteur de double représentant la matrice </returns>
    std::vector<double> getContentAsStdVector() const;

    /// <summary>
    /// Méthode permettant de récupérer la valeur de la matrice située ligne line et colonne column
    /// </summary>
    /// <param name="line"> La ligne de l'élément que l'on souhaite récupérer </param>
    /// <param name="column"> La colonne de l'élément que l'on souhaite récupérer </param>
    /// <returns> L'élément de la matrice situé à la ligne line et à la colonne column </returns>
    double operator()(int line, int column) const;

    /// <summary>
    /// Setter de Matrix4D
    /// </summary>
    /// <param name="line"> Ligne de l'élement que l'on souhaite modifier </param>
    /// <param name="column"> Colonne de l'élément que l'on souhaite modifier </param>
    /// <returns> L'élément que l'on a modifié </returns>
    double& operator()(int line, int column);

    /// <summary>
    /// Méthode permettant d'attribuer le contenu d'une matrice dans une autre matrice
    /// </summary>
    /// <param name="matrix4D"> La matrice dont on souhaite copier les valeurs </param>
    void operator=(const Matrix4D& matrix4D);

    /// <summary>
    /// Surcharge de l'opérateur +=
    /// </summary>
    /// <param name="matrix4D"> La matrice que l'on veut additionner à notre matrice </param>
    /// <returns> La somme de la matrice considérée et de matrix4D </returns>
    Matrix4D operator+=(const Matrix4D& matrix4D);

    /// <summary>
    /// Surcharge de l'opérateur -=
    /// </summary>
    /// <param name="matrix4D"> La matrice que l'on veut soustraire à notre matrice </param>
    /// <returns> La différence de la matrice considérée et de matrix4D </returns>
    Matrix4D operator-=(const Matrix4D& matrix4D);

    /// <summary>
    /// Méthode permettant de calculer la transposée de la matrice considérée
    /// </summary>
    /// <returns> La transposée de la matrice considérée </returns>
    Matrix4D transpose() const;

    /// <summary>
    /// Méthode permettant de calculer l'inverse de la matrice considérée, si cela est possible
    /// </summary>
    /// <returns> L'inverse de la matrice considérée, s'il existe </returns>
    Matrix4D invert() const;

    /// <summary>
    /// Stocke la transposée de la matrice 4D dans le tableau de float passé en argument
    /// </summary>
    void toFloatArray(float arr[]);

    /// <summary>
    /// Méthode permettant de créer la matrice identité
    /// </summary>
    /// <returns> La matrice identité </returns>
    static Matrix4D identity();

    /// <summary>
    /// Méthode permettant de créer une matrice de translation
    /// </summary>
    /// <param name="vect"> Le vecteur de translation </param>
    /// <returns> La matrice de translation associée au vecteur de translation </returns>
    static Matrix4D translation(const Vecteur3D &vect);

    /// <summary>
    /// Méthode permettant de créer une matrice de mise à l'échelle
    /// </summary>
    /// <param name="vect"> Le vecteur de mise à l'échelle </param>
    /// <returns> La matrice de mise à l'échelle associée au vecteur de mise à l'échelle </returns>
    static Matrix4D scaling(const Vecteur3D& vect);

    //static Matrix4D rotation(Vecteur3D& vect);

};

/// <summary>
/// Surcharge de l'opérateur +
/// </summary>
/// <param name="matrix4D_1"> La première matrice que l'on souhaite additionner </param>
/// <param name="matrix4D_2"> La seconde matrice que l'on souhaite additionner </param>
/// <returns> La somme des deux matrices </returns>
Matrix4D operator+(const Matrix4D& matrix4D_1, const Matrix4D& matrix4D_2);

/// <summary>
/// Surcharge de l'opérateur -
/// </summary>
/// <param name="matrix4D_1"> La première matrice que l'on souhaite soustraire </param>
/// <param name="matrix4D_2"> La seconde matrice que l'on souhaite soustraire </param>
/// <returns> La différence des deux matrices </returns>
Matrix4D operator-(const Matrix4D& matrix4D_1, const Matrix4D& matrix4D_2);

/// <summary>
/// Surcharge de l'opérateur *
/// </summary>
/// <param name="matrix4D"> La matrice que l'on souhaite multiplier </param>
/// <param name="multiplier"> Le scalaire par lequel on souhaite multiplier notre matrice </param>
/// <returns> La matrice résultat de cette multiplication </returns>
Matrix4D operator*(const Matrix4D& matrix4D, const double& multiplier);

/// <summary>
/// Surcharge de l'opérateur *
/// </summary>
/// <param name="multiplier"> Le scalaire par lequel on souhaite multiplier notre matrice </param>
/// <param name="matrix4D"> La matrice que l'on souhaite multiplier </param>
/// <returns> La matrice résultat de cette multiplication </returns>
Matrix4D operator*(const double& multiplier, const Matrix4D& matrix4D);

/// <summary>
/// Surcharge de l'opérateur *
/// </summary>
/// <param name="matrix4D_1"> La première matrice que l'on souhaite multiplier </param>
/// <param name="matrix4D_2"> La seconde matrice que l'on souhaite multiplier </param>
/// <returns> La matrice résultat de cette multiplication </returns>
Matrix4D operator*(const Matrix4D& matrix4D_1, const Matrix4D& matrix4D_2);

/// <summary>
/// Surcharge de l'opérateur == 
/// </summary>
/// <param name="matrix4D_1"> La première matrice que l'on souhaite comparer </param>
/// <param name="matrix4D_2"> La seconde matrice que l'on souhaite comparer </param>
/// <returns> True si les deux matrices sont de contenu égal, false sinon </returns>
bool operator==(const Matrix4D& matrix4D_1, const Matrix4D& matrix4D_2);

/// <summary>
/// Surcharge de l'opérateur <<,^permettant d'afficher une matrice 
/// </summary>
/// <param name="out"> Le flux sur lequel on veut écrire </param>
/// <param name="matrix4D"> La matrice que l'on souhaite afficher </param>
/// <returns> Le flux dans lequel est écrit notre matrice </returns>
std::ostream& operator<<(std::ostream& out, const Matrix4D& matrix4D);

#endif
