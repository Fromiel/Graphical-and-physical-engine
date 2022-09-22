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

    Matrix4D();
    Matrix4D(const std::vector<double>& content);
    Matrix4D(const Matrix4D& matrix4D);

    std::vector<double> getContentAsStdVector() const;

    double operator()(int line, int column) const;
    double& operator()(int line, int column);
    void operator=(const Matrix4D& matrix4D);

    Matrix4D operator+=(const Matrix4D& matrix4D);
    Matrix4D operator-=(const Matrix4D& matrix4D);

    Matrix4D transpose() const;
    Matrix4D invert() const;

    static Matrix4D identity();
    static Matrix4D translation(Vecteur3D &vect);
    static Matrix4D scaling(Vecteur3D& vect);
    //static Matrix4D rotation(Vecteur3D& vect);

    static Matrix4D modelMatrix(Vecteur3D &translation, Vecteur3D &scaling);
    static Matrix4D viewMatrix(Vecteur3D &cameraPosition);
    static Matrix4D projectionMatrix(float radianFov, float ratio, float near, float far);
};

Matrix4D operator+(const Matrix4D& matrix4D_1, const Matrix4D& matrix4D_2);
Matrix4D operator-(const Matrix4D& matrix4D_1, const Matrix4D& matrix4D_2);

Matrix4D operator*(const Matrix4D& matrix4D, const double& multiplier);
Matrix4D operator*(const double& multiplier, const Matrix4D& matrix4D);

Matrix4D operator*(const Matrix4D& matrix4D_1, const Matrix4D& matrix4D_2);

bool operator==(const Matrix4D& matrix4D_1, const Matrix4D& matrix4D_2);

std::ostream& operator<<(std::ostream& out, const Matrix4D& matrix4D);

#endif
