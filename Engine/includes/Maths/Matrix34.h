#ifndef MATRIX34_H
#define MATRIX34_H

#include <iostream>
#include <vector>

#include <algorithm>
#include <functional>

#include "Maths/Matrix4D.h"
#include "Maths/Vecteur3D.h"
#include "Maths/Quaternion.h"
#include "Maths/Matrix3D.h"

class Matrix34 {
    private:
        std::vector<double> content;

    public:
        static const int lineCount = 3;
        static const int columnCount = 4;

        Matrix34();
        Matrix34(const std::vector<double> &content);
        Matrix34(const Matrix34 &other);
        ~Matrix34();

        std::vector<double> getContentAsStdVector() const;
        
        Matrix34 inverse();
        void setOrientationAndPosition(const Quaternion &quaternion, const Vecteur3D &vector);
        Vecteur3D transformPosition(const Vecteur3D &position);
        Vecteur3D transformDirection(const Vecteur3D &direction);


        void toFloatArray(float* arr);

        /// <summary>
        /// Retourne la matrice de scale
        /// </summary>
        /// <param name="scale"></param>
        /// <returns></returns>
        static Matrix34 scaling(const Vecteur3D &scale);

        double operator()(const int &line, const int &column) const;
        double& operator()(int line, int colonne);
        void operator=(const Matrix34 &matrix);

        Matrix34 operator+=(const Matrix34 &matrix);
        Matrix34 operator-=(const Matrix34 &matrix);

        friend Matrix34 operator+(const Matrix34 &matrix_1, const Matrix34 &matrix_2);
        friend Matrix34 operator-(const Matrix34 &matrix_1, const Matrix34 &matrix_2);

        friend Matrix34 operator*(const Matrix34 &matrix, const double &multiplier);
        friend Matrix34 operator*(const double &multiplier, const Matrix34 &matrix);

        friend Matrix34 operator*(const Matrix34 &matrix_1, const Matrix34 &matrix_2);
        friend Vecteur3D operator*(const Matrix34 &matrix, const Vecteur3D &vector);

        friend Matrix3D operator*(const Matrix34&, const Matrix3D&);
        friend Matrix3D operator*(const Matrix3D&, const Matrix34&);

        /// <summary>
        /// Surcharge de l'opérateur * pour multiplier une matrice 4D avec une matrice34
        /// </summary>
        /// <param name="matrix4D"></param>
        /// <param name="matrix34"></param>
        /// <returns></returns>
        friend Matrix4D operator*(const Matrix4D& matrix4D, const Matrix34& matrix34);

        friend bool operator==(const Matrix34 &matrix_1, const Matrix34 &matrix_2);

        friend std::ostream &operator<<(std::ostream &out, const Matrix34 &matrix);
};

#endif
