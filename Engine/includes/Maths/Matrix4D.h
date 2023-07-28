#ifndef MATRIX4D_H
#define MATRIX4D_H

#include <ostream>
#include <vector>

/// <summary>
/// Matrix 4*4 (matrix(i,j) is the value at i-1 line and j-1 column)
/// </summary>
class Matrix4D {
private:
    double content_[16]; // Contain the 16 values of the matrix, in a 1D array

public:
    static const int lineCount = 4;
    static const int columnCount = 4;
    
    /// <summary>
    /// Constructor of Matrix4D, with default value the null matrix
    /// </summary>
    Matrix4D();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="content">Values of the matrix</param>
    Matrix4D(const std::vector<double>& content);

    /// <summary>
    /// Getter of content_
    /// </summary>
    /// <returns> A vector of double representing the matrix. </returns>
    std::vector<double> getContentAsStdVector() const;

    double operator()(int line, int column) const;
    double& operator()(int line, int column);
    void operator=(const Matrix4D& matrix4D);
    Matrix4D operator+=(const Matrix4D& matrix4D);
    Matrix4D operator-=(const Matrix4D& matrix4D);

    /// <summary>
    /// Calculate the transpose of the matrix
    /// </summary>
    /// <returns> The transpose </returns>
    Matrix4D transpose() const;

    /// <summary>
    /// Invert the matrix (if it isn't possible, throw an error)
    /// </summary>
    /// <returns> The invert of the matrix </returns>
    Matrix4D invert() const;

    /// <summary>
    /// Store the transpose of the 3D matrix in the float array passed as argument 
    /// (because in glsl, matrix(i, j) is the value at j-1 line and i-1 column)
    /// </summary>
    void toFloatArray(float arr[]);

    /// <summary>
    /// Create the identity matrix
    /// </summary>
    /// <returns>The identity matrix</returns>
    static Matrix4D identity();


    friend Matrix4D operator+(const Matrix4D& matrix4D_1, const Matrix4D& matrix4D_2);
    friend Matrix4D operator-(const Matrix4D& matrix4D_1, const Matrix4D& matrix4D_2);
    friend Matrix4D operator*(const Matrix4D& matrix4D, const double& multiplier);
    friend Matrix4D operator*(const double& multiplier, const Matrix4D& matrix4D);
    friend Matrix4D operator*(const Matrix4D& matrix4D_1, const Matrix4D& matrix4D_2);
    friend bool operator==(const Matrix4D& matrix4D_1, const Matrix4D& matrix4D_2);
    friend std::ostream& operator<<(std::ostream& out, const Matrix4D& matrix4D);
};

#endif
