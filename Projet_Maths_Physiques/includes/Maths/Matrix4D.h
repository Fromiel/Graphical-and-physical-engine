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
    /// Constructeur non valu� de Matrix4D, avec comme valeur par d�faut la matrice nulle
    /// </summary>
    Matrix4D();

    /// <summary>
    /// Constructeur valu� de Matrix4D
    /// </summary>
    /// <param name="content">Un vecteur repr�sentant le contenu de la matrice</param>
    Matrix4D(const std::vector<double>& content);

    /// <summary>
    /// Constructeur de copie de Matrix4D
    /// </summary>
    /// <param name="matrix4D"> La matrice dont on veut copier le contenu </param>
    Matrix4D(const Matrix4D& matrix4D);

    /// <summary>
    /// Getter de _content
    /// </summary>
    /// <returns> Un vecteur de double repr�sentant la matrice </returns>
    std::vector<double> getContentAsStdVector() const;

    /// <summary>
    /// M�thode permettant de r�cup�rer la valeur de la matrice situ�e ligne line et colonne column
    /// </summary>
    /// <param name="line"> La ligne de l'�l�ment que l'on souhaite r�cup�rer </param>
    /// <param name="column"> La colonne de l'�l�ment que l'on souhaite r�cup�rer </param>
    /// <returns> L'�l�ment de la matrice situ� � la ligne line et � la colonne column </returns>
    double operator()(int line, int column) const;

    /// <summary>
    /// Setter de Matrix4D
    /// </summary>
    /// <param name="line"> Ligne de l'�lement que l'on souhaite modifier </param>
    /// <param name="column"> Colonne de l'�l�ment que l'on souhaite modifier </param>
    /// <returns> L'�l�ment que l'on a modifi� </returns>
    double& operator()(int line, int column);

    /// <summary>
    /// M�thode permettant d'attribuer le contenu d'une matrice dans une autre matrice
    /// </summary>
    /// <param name="matrix4D"> La matrice dont on souhaite copier les valeurs </param>
    void operator=(const Matrix4D& matrix4D);

    /// <summary>
    /// Surcharge de l'op�rateur +=
    /// </summary>
    /// <param name="matrix4D"> La matrice que l'on veut additionner � notre matrice </param>
    /// <returns> La somme de la matrice consid�r�e et de matrix4D </returns>
    Matrix4D operator+=(const Matrix4D& matrix4D);

    /// <summary>
    /// Surcharge de l'op�rateur -=
    /// </summary>
    /// <param name="matrix4D"> La matrice que l'on veut soustraire � notre matrice </param>
    /// <returns> La diff�rence de la matrice consid�r�e et de matrix4D </returns>
    Matrix4D operator-=(const Matrix4D& matrix4D);

    /// <summary>
    /// M�thode permettant de calculer la transpos�e de la matrice consid�r�e
    /// </summary>
    /// <returns> La transpos�e de la matrice consid�r�e </returns>
    Matrix4D transpose() const;

    /// <summary>
    /// M�thode permettant de calculer l'inverse de la matrice consid�r�e, si cela est possible
    /// </summary>
    /// <returns> L'inverse de la matrice consid�r�e, s'il existe </returns>
    Matrix4D invert() const;

    /// <summary>
    /// Stocke la transpos�e de la matrice 4D dans le tableau de float pass� en argument
    /// </summary>
    void toFloatArray(float arr[]);

    /// <summary>
    /// M�thode permettant de cr�er la matrice identit�
    /// </summary>
    /// <returns> La matrice identit� </returns>
    static Matrix4D identity();

    /// <summary>
    /// M�thode permettant de cr�er une matrice de translation
    /// </summary>
    /// <param name="vect"> Le vecteur de translation </param>
    /// <returns> La matrice de translation associ�e au vecteur de translation </returns>
    static Matrix4D translation(const Vecteur3D &vect);

    /// <summary>
    /// M�thode permettant de cr�er une matrice de mise � l'�chelle
    /// </summary>
    /// <param name="vect"> Le vecteur de mise � l'�chelle </param>
    /// <returns> La matrice de mise � l'�chelle associ�e au vecteur de mise � l'�chelle </returns>
    static Matrix4D scaling(const Vecteur3D& vect);

    //static Matrix4D rotation(Vecteur3D& vect);

};

/// <summary>
/// Surcharge de l'op�rateur +
/// </summary>
/// <param name="matrix4D_1"> La premi�re matrice que l'on souhaite additionner </param>
/// <param name="matrix4D_2"> La seconde matrice que l'on souhaite additionner </param>
/// <returns> La somme des deux matrices </returns>
Matrix4D operator+(const Matrix4D& matrix4D_1, const Matrix4D& matrix4D_2);

/// <summary>
/// Surcharge de l'op�rateur -
/// </summary>
/// <param name="matrix4D_1"> La premi�re matrice que l'on souhaite soustraire </param>
/// <param name="matrix4D_2"> La seconde matrice que l'on souhaite soustraire </param>
/// <returns> La diff�rence des deux matrices </returns>
Matrix4D operator-(const Matrix4D& matrix4D_1, const Matrix4D& matrix4D_2);

/// <summary>
/// Surcharge de l'op�rateur *
/// </summary>
/// <param name="matrix4D"> La matrice que l'on souhaite multiplier </param>
/// <param name="multiplier"> Le scalaire par lequel on souhaite multiplier notre matrice </param>
/// <returns> La matrice r�sultat de cette multiplication </returns>
Matrix4D operator*(const Matrix4D& matrix4D, const double& multiplier);

/// <summary>
/// Surcharge de l'op�rateur *
/// </summary>
/// <param name="multiplier"> Le scalaire par lequel on souhaite multiplier notre matrice </param>
/// <param name="matrix4D"> La matrice que l'on souhaite multiplier </param>
/// <returns> La matrice r�sultat de cette multiplication </returns>
Matrix4D operator*(const double& multiplier, const Matrix4D& matrix4D);

/// <summary>
/// Surcharge de l'op�rateur *
/// </summary>
/// <param name="matrix4D_1"> La premi�re matrice que l'on souhaite multiplier </param>
/// <param name="matrix4D_2"> La seconde matrice que l'on souhaite multiplier </param>
/// <returns> La matrice r�sultat de cette multiplication </returns>
Matrix4D operator*(const Matrix4D& matrix4D_1, const Matrix4D& matrix4D_2);

/// <summary>
/// Surcharge de l'op�rateur == 
/// </summary>
/// <param name="matrix4D_1"> La premi�re matrice que l'on souhaite comparer </param>
/// <param name="matrix4D_2"> La seconde matrice que l'on souhaite comparer </param>
/// <returns> True si les deux matrices sont de contenu �gal, false sinon </returns>
bool operator==(const Matrix4D& matrix4D_1, const Matrix4D& matrix4D_2);

/// <summary>
/// Surcharge de l'op�rateur <<,^permettant d'afficher une matrice 
/// </summary>
/// <param name="out"> Le flux sur lequel on veut �crire </param>
/// <param name="matrix4D"> La matrice que l'on souhaite afficher </param>
/// <returns> Le flux dans lequel est �crit notre matrice </returns>
std::ostream& operator<<(std::ostream& out, const Matrix4D& matrix4D);

#endif
