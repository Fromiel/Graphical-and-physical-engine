#ifndef MATRIX34_H
#define MATRIX34_H

#include <iostream>
#include <vector>

#include <algorithm>
#include <functional>

#include "Maths/Vecteur3D.h"
#include "Maths/Quaternion.h"

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
        Vecteur3D transformPosition(const Vecteur3D &vector);
        Vecteur3D transformDirection(const Vecteur3D &vector);

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

        friend bool operator==(const Matrix34 &matrix_1, const Matrix34 &matrix_2);

        friend std::ostream &operator<<(std::ostream &out, const Matrix34 &matrix);
};

#endif
