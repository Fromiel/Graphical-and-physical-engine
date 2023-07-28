#ifndef MATRIX3D_H
#define MATRIX3D_H

#include <ostream>
#include <vector>
#include "Vector3D.h"

/// <summary>
/// 3 * 3 matrix (matrix(i,j) is the value at i-1 line and j-1 column)
/// </summary>
class Matrix3D {
    private:
        double content_[9]; // contains the 9 values of the 3*3 matrix

    public:
        static const int lineCount = 3;
        static const int columnCount = 3;

        /// <summary>
        /// Constructor of Matrix4D, with default value the null matrix
        /// </summary>
        Matrix3D();

        /// <summary>
        /// 
        /// </summary>
        /// <param name="content">Values of the matrix</param>
        Matrix3D(const std::vector<double> &content);

        /// <summary>
        /// Getter of content_
        /// </summary>
        /// <returns> A vector of double representing the matrix. </returns>
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
        /// Store the transpose of the 3D matrix in the float array passed as argument 
        /// (because in glsl, matrix(i, j) is the value at j-1 line and i-1 column)
        /// </summary>
        void toFloatArray(float arr[]);


        static Matrix3D identity();


        friend Matrix3D operator+(const Matrix3D& matrix3D_1, const Matrix3D& matrix3D_2);

        friend Matrix3D operator-(const Matrix3D& matrix3D_1, const Matrix3D& matrix3D_2);

        friend Matrix3D operator*(const Matrix3D& matrix3D, const double& multiplier);
        friend Matrix3D operator*(const double& multiplier, const Matrix3D& matrix3D);
        friend Vector3D operator*(const Matrix3D& matrix3D, const Vector3D& vecteur3D);

        friend Matrix3D operator*(const Matrix3D& matrix3D_1, const Matrix3D& matrix3D_2);

        friend bool operator==(const Matrix3D& matrix3D_1, const Matrix3D& matrix3D_2);

        friend std::ostream& operator<<(std::ostream& out, const Matrix3D& matrix3D);
};

#endif
