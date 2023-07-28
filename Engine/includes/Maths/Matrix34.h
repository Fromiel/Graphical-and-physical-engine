#ifndef MATRIX34_H
#define MATRIX34_H

#include <iostream>
#include <vector>

#include "Maths/Matrix4D.h"
#include "Maths/Vector3D.h"
#include "Maths/Quaternion.h"
#include "Maths/Matrix3D.h"

/// <summary>
/// Use to store 4*4 matrix (only 3 lines are stored for optimization, the last one is implicit : (0, 0, 0, 1))
/// </summary>
class Matrix34 {
    private:
        double content_[12]; //The three lines stored

    public:
        static const int lineCount = 3;
        static const int columnCount = 4;

        /// <summary>
        /// Constructor of Matrix34, with default value the null matrix
        /// </summary>
        Matrix34();

        /// <summary>
        /// 
        /// </summary>
        /// <param name="content">Values of the matrix</param>
        Matrix34(const std::vector<double> &content);

        /// <summary>
        /// Getter of content_
        /// </summary>
        /// <returns> A vector of double representing the matrix. </returns>
        std::vector<double> getContentAsStdVector() const;
        
        Matrix34 invert();

        /// <summary>
        /// Create the transformation matrix with rotation set with the quaternion and the translation set with vector 
        /// </summary>
        /// <param name="quaternion"></param>
        /// <param name="vector"></param>
        void setOrientationAndPosition(const Quaternion &quaternion, const Vector3D &vector);

        /// <summary>
        /// Return the vector of the postion translated by the matrix
        /// </summary>
        /// <param name="position"></param>
        /// <returns></returns>
        Vector3D transformPosition(const Vector3D &position);

        /// <summary>
        /// Return the vector of the direction rotated by the matrix
        /// </summary>
        /// <param name="direction"></param>
        /// <returns></returns>
        Vector3D transformDirection(const Vector3D &direction);

        /// <summary>
        /// Store the transpose of the 3D matrix in the float array passed as argument 
        /// (because in glsl, matrix(i, j) is the value at j-1 line and i-1 column)
        /// WARNING : the array must be of size 16
        /// </summary>
        void toFloatArray(float* arr);

        /// <summary>
        /// Calculate the scale matrix
        /// </summary>
        /// <param name="scale"></param>
        /// <returns></returns>
        static Matrix34 scaling(const Vector3D &scale);

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

        /// <summary>
        /// Overload of the operator * to multiply a 34 matrix with a 3D vector (the 3rd vector is implicitely a homogen vector with a 1 as fourth value)
        /// </summary>
        /// <param name="matrix"></param>
        /// <param name="vector"></param>
        /// <returns></returns>
        friend Vector3D operator*(const Matrix34 &matrix, const Vector3D &vector);

        /// <summary>
        /// Overload of the operator * to multiply a 34 matrix with a 3D matrix
        /// Take the 3*3 matrix of the 34 matrix (upper left) and multiply it with the 3D matrix
        /// </summary>
        /// <param name=""></param>
        /// <param name=""></param>
        /// <returns></returns>
        friend Matrix3D operator*(const Matrix34&, const Matrix3D&);

        /// <summary>
        /// Overload of the operator * to multiply a 3D matrix with a 34 matrix
        /// Take the 3*3 matrix of the 34 matrix (upper left) and multiply it with the 3D matrix
        /// </summary>
        /// <param name=""></param>
        /// <param name=""></param>
        /// <returns></returns>
        friend Matrix3D operator*(const Matrix3D&, const Matrix34&);

        /// <summary>
        /// Overload of the operator * to multiply a 4D matrix with a 34 matrix
        /// </summary>
        /// <param name="matrix4D"></param>
        /// <param name="matrix34"></param>
        /// <returns></returns>
        friend Matrix4D operator*(const Matrix4D& matrix4D, const Matrix34& matrix34);

        /// <summary>
        /// Overload of the operator * to multiply a 34 matrix with a 4D matrix
        /// </summary>
        /// <param name="matrix4D"></param>
        /// <param name="matrix34"></param>
        /// <returns></returns>
        friend Matrix4D operator*(const Matrix34& matrix34, const Matrix4D& matrix4D);

        friend bool operator==(const Matrix34 &matrix_1, const Matrix34 &matrix_2);

        friend std::ostream &operator<<(std::ostream &out, const Matrix34 &matrix);
};

#endif
