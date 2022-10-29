#ifndef MATRIX3D_H
#define MATRIX3D_H

#include <ostream>
#include <vector>

#include <algorithm>
#include <functional>

class Matrix3D {
    private:
        std::vector<double> content;

    public:
        static const int lineCount = 3;
        static const int columnCount = 3;

        Matrix3D();
        Matrix3D(const std::vector<double> &content);
        Matrix3D(const Matrix3D &matrix3D);

        std::vector<double> getContentAsStdVector() const;
        
        double operator()(const int &line, const int &column) const;
        double& operator()(int line, int colonne);
        void operator=(const Matrix3D &matrix3D);

        Matrix3D operator+=(const Matrix3D &matrix3D);
        Matrix3D operator-=(const Matrix3D &matrix3D);

        double determinant() const;
        Matrix3D normalize() const;
        Matrix3D transpose() const;
        Matrix3D adjugate() const;
        Matrix3D invert() const;

        /// <summary>
        /// Stocke la transposée de la matrice 3D dans le tableau de float passé en argument
        /// </summary>
        void toFloatArray(float arr[]);

        static Matrix3D identity();
};

Matrix3D operator+(const Matrix3D &matrix3D_1, const Matrix3D &matrix3D_2);
Matrix3D operator-(const Matrix3D &matrix3D_1, const Matrix3D &matrix3D_2);

Matrix3D operator*(const Matrix3D &matrix3D, const double &multiplier);
Matrix3D operator*(const double &multiplier, const Matrix3D &matrix3D);

Matrix3D operator*(const Matrix3D &matrix3D_1, const Matrix3D &matrix3D_2);

bool operator==(const Matrix3D &matrix3D_1, const Matrix3D &matrix3D_2);

std::ostream &operator<<(std::ostream &out, const Matrix3D &matrix3D);

#endif
