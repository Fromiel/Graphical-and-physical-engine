/**
 * \file Matrice.cpp
 * \brief Implémentation des matrices carrées.
 *
 * Fichier source du fichier Matrice.h. Implémentation des membres de la classe Matrice, de ses constructeurs,
 * de ses opérateurs internes et des opérateurs externes, et d'autres fonctions.
 */

#include "Matrice.h"
#include <cmath>

Matrice::Matrice(int n) {
    if (n < 1) throw "Matrice::Matrice -> Erreur : Taille incorrecte.";
    data_ = new float[n*n];
    n_ = n;
}

Matrice::Matrice(const Matrice &mat) {
    n_ = mat.get_n();
    data_ = new float[n_*n_];
    for (int i = 0; i < n_*n_; i++) {
        data_[i] = mat(i/mat.get_n(), i%mat.get_n());
    }
}

Matrice::~Matrice() {
    delete[] data_;
}

int Matrice::get_n() const{
    return n_;
}

float & Matrice::operator()(int i, int j) {
    if (i < 0 || i > get_n()-1 || j < 0 || j > get_n()-1) {
        throw "Matrice::operator() -> Erreur : Indices invalides.";
    }
    return data_[i*n_ + j];
}

float Matrice::operator()(int i, int j) const {
    if (i < 0 || i > get_n()-1 || j < 0 || j > get_n()-1) {
        throw "Matrice::operator() -> Erreur : Indices invalides.";
    }
    return data_[i*n_ + j];
}
Matrice & Matrice::operator=(const Matrice mat) {
    n_ = mat.get_n();
    data_ = new float[n_*n_];
    for (int i = 0; i < n_*n_; i++) {
        data_[i] = mat(i/mat.get_n(), i%mat.get_n());
    }
    return *this;
}

Matrice Matrice::transp(Matrice mat) {
    Matrice res(mat.get_n());
    for (int i = 0; i < res.get_n(); i++) {
        for (int j = 0; j < res.get_n(); j++) {
            res(i,j) = mat(j, i);
        }
    }
    return res;
}

std::ostream & operator<<(std::ostream & st, const Matrice &mat) {
    for (int i = 0; i < mat.get_n(); i++){ /*!< Affichage de la matrice sous la forme [mat(0,0), mat(0,1), mat(0,2)] \n ... \n [mat(2,0), mat(2,1), mat(2,2)] */
        for (int j = 0; j < mat.get_n(); j++) {
            if (j == 0) st << '[';
            st << mat(i,j);
            if (i < mat.get_n()-1) st << ',';
            if (j == mat.get_n()-1) st << ']' << std::endl;
        }
    }
    return st;
}

Matrice operator+(const Matrice & mat1, const Matrice & mat2) {
    if (mat1.get_n() != mat2.get_n()) throw "operator+ -> Erreur : Les matrices sont de tailles differentes.";
    Matrice res(mat1.get_n());
    for (int i = 0; i < res.get_n(); i++) {
        for (int j = 0; j < res.get_n(); j++) {
            res(i,j) = mat1(i,j) + mat2(i,j);
        }
    }
    return res;
}

Matrice operator-(const Matrice & mat1, const Matrice & mat2) {
    if (mat1.get_n() != mat2.get_n()) throw "operator- -> Erreur : Les matrices sont de tailles differentes.";
    Matrice res(mat1.get_n());
    for (int i = 0; i < res.get_n(); i++) {
        for (int j = 0; j < res.get_n(); j++) {
            res(i,j) = mat1(i,j) - mat2(i,j);
        }
    }
    return res;
}

Matrice operator*(const Matrice & mat1, const Matrice & mat2) {
    if (mat1.get_n() != mat2.get_n()) throw "operator* -> Erreur : Produit matriciel impossible";
    Matrice res(mat1.get_n());
    for (int i = 0; i < res.get_n(); i++) {
        for (int j = 0; j < res.get_n(); j++) {
            float somme = 0;
            for (int k = 0; k < mat1.get_n(); k++) {
                somme += mat1(i,k) * mat2(k,j);
            }
            res(i,j) = somme;
        }
    }
    return res;
}

Matrice operator*(const Matrice & mat, float x) {
    Matrice res(mat.get_n());
    for (int i = 0; i < res.get_n(); i++) {
        for (int j = 0; j < res.get_n(); j++) {
            res(i,j) = x * mat(i,j);
        }
    }
    return res;
}

Matrice operator*(float x, const Matrice & mat) {
    Matrice res(mat.get_n());
    for (int i = 0; i < res.get_n(); i++) {
        for (int j = 0; j < res.get_n(); j++) {
            res(i,j) = x * mat(i,j);
        }
    }
    return res;
}

Vecteur3D operator*(const Matrice & mat, const Vecteur3D & p) {
    if (mat.get_n() != 3) throw "operator* -> Erreur : La taille de la matrice est invalide (!= 3).";
    Vecteur3D res(mat(0, 0) * p.get_x() + mat(0, 1) * p.get_y() + mat(0, 2) * p.get_z(),
                mat(1, 0) * p.get_x() + mat(1, 1) * p.get_y() + mat(1, 2) * p.get_z(),
                mat(2, 0) * p.get_x() + mat(2, 1) * p.get_y() + mat(2, 2) * p.get_z());
    return res;
}

Vecteur2D operator*(const Matrice & mat, const Vecteur2D & p) {
    if (mat.get_n() != 3) throw "operator* -> Erreur : La taille de la matrice est invalide (!= 2).";
    Vecteur2D res(mat(0, 0) * p.get_x() + mat(0, 1) * p.get_y(),
                mat(1, 0) * p.get_x() + mat(1, 1) * p.get_y());
    return res;
}

Matrice operator/(const Matrice & mat, float x) {
    if (x == 0) throw "operator/ -> Erreur : Division par 0.";
    Matrice res(mat.get_n());
    for (int i = 0; i < res.get_n(); i++) {
        for (int j = 0; j < res.get_n(); j++) {
            res(i,j) = mat(i,j) / x;
        }
    }
    return res;
}

Matrice Mat_Rotation(Vecteur3D axe, float rotation) {
    Vecteur3D axe_unitaire(axe/axe.norme()); /*!< On normalise l'axe pour pouvoir utiliser la formule des matrices de rotations */
    float c = cos(rotation), s = sin(rotation);
    Matrice res(3);
    res(0, 0) = axe_unitaire.get_x() * axe_unitaire.get_x() * (1 - c) + c;
    res(0, 1) = axe_unitaire.get_x() * axe_unitaire.get_y() * (1 - c) - axe_unitaire.get_z() * s;
    res(0, 2) = axe_unitaire.get_x() * axe_unitaire.get_z() * (1 - c) + axe_unitaire.get_y() * s;
    res(1, 0) = axe_unitaire.get_x() * axe_unitaire.get_y() * (1 - c) + axe_unitaire.get_z() * s;
    res(1, 1) = axe_unitaire.get_y() * axe_unitaire.get_y() * (1 - c) + c;
    res(1, 2) = axe_unitaire.get_y() * axe_unitaire.get_z() * (1 - c) - axe_unitaire.get_x() * s;
    res(2, 0) = axe_unitaire.get_x() * axe_unitaire.get_z() * (1 - c) - axe_unitaire.get_y() * s;
    res(2, 1) = axe_unitaire.get_y() * axe_unitaire.get_z() * (1 - c) + axe_unitaire.get_x() * s;
    res(2, 2) = axe_unitaire.get_z() * axe_unitaire.get_z() * (1 - c) + c;
    return res;
}

Matrice Mat_Projection(float FOVx, float FOVy, float Zmin, float Zmax) {
    Matrice res(3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i != j) res(i,j) = 0;
        }
    }
    res(0,0) = atan(FOVx / 2);
    res(1,1) = atan(FOVy / 2);
    res(2, 2) = - (Zmax + Zmin) / (Zmax - Zmin);
    return res;
}