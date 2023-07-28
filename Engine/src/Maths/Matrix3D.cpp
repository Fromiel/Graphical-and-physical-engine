#include "Maths/Matrix3D.h"

#include <algorithm>
#include <functional>

const float epsilon = 0.0001f;

Matrix3D::Matrix3D() : content_{} {}

Matrix3D::Matrix3D(const std::vector<double>& content) : content_{} {
    if (content.size() != 9) throw std::invalid_argument("Matrix3D::Provide content with size 9");

    for (size_t i = 0; i < 9; i++)
        content_[i] = content[i];

    return;
}

std::vector<double> Matrix3D::getContentAsStdVector() const {
    return std::vector<double>(content_, content_ + 9);
}

void Matrix3D::toFloatArray(float arr[])
{
    std::vector<double> content = this->transpose().getContentAsStdVector();
    std::copy(content.begin(), content.end(), arr);
}

double Matrix3D::operator()(const int &line, const int &column) const {
    if (line < 0 || line > 2 || column < 0 || column > 2) {
        throw std::invalid_argument("Matrix3D::Provide line and column inferior to 3");
    }
    return content_[Matrix3D::columnCount * line + column];
}

double& Matrix3D::operator()(const int line, const int column) {
    if (line < 0 || line > 2 || column < 0 || column > 2) {
        throw std::invalid_argument("Matrix3D::Provide line and column inferior to 3");
    }
    return content_[Matrix3D::columnCount * line + column];
}

void Matrix3D::operator=(const Matrix3D &matrix3D) {
    for (size_t i = 0; i < 9; i++)
        content_[i] = matrix3D.content_[i];;
    return;
}

Matrix3D Matrix3D::operator+=(const Matrix3D &matrix3D) {
    for (size_t i = 0; i < 9; i++)
        content_[i] += matrix3D.content_[i];
    
    return *this;
}

Matrix3D Matrix3D::operator-=(const Matrix3D &matrix3D) {
    for (size_t i = 0; i < 9; i++)
        content_[i] -= matrix3D.content_[i];

    return *this;
}

double Matrix3D::determinant() const {
    return 
        content_[0] * (content_[4]*content_[8] - content_[5]*content_[7]) -
        content_[1] * (content_[3]*content_[8] - content_[5]*content_[6]) +
        content_[2] * (content_[3]*content_[7] - content_[4]*content_[6])
    ;
}

Matrix3D Matrix3D::normalize() const {
    const double determinant = this->determinant();
    if (determinant == 0) throw(std::invalid_argument("Matrix3D::Cannot normalize, determinant is 0"));

    std::vector<double> content_out = getContentAsStdVector();
    std::transform(content_out.begin(), content_out.end(), content_out.begin(), [&determinant](double &nb) {
        return nb / determinant;
    });
    return Matrix3D(content_out);
}

Matrix3D Matrix3D::transpose() const {
    Matrix3D matrix_out = Matrix3D({
        content_[0], content_[3], content_[6],
        content_[1], content_[4], content_[7],
        content_[2], content_[5], content_[8]
    });
    return matrix_out;
}

Matrix3D Matrix3D::adjugate() const {
    Matrix3D transpose = this->transpose();
    std::vector<double> adjugateContent = std::vector<double>(9, 0);
    adjugateContent[0] += transpose(1, 1)*transpose(2, 2) - transpose(2, 1)*transpose(1, 2);
    adjugateContent[1] -= transpose(0, 1)*transpose(2, 2) - transpose(2, 1)*transpose(0, 2);
    adjugateContent[2] += transpose(0, 1)*transpose(1, 2) - transpose(1, 1)*transpose(0, 2);
    adjugateContent[3] -= transpose(1, 0)*transpose(2, 2) - transpose(2, 0)*transpose(1, 2);
    adjugateContent[4] += transpose(0, 0)*transpose(2, 2) - transpose(2, 0)*transpose(0, 2);
    adjugateContent[5] -= transpose(0, 0)*transpose(1, 2) - transpose(1, 0)*transpose(0, 2);
    adjugateContent[6] += transpose(1, 0)*transpose(2, 1) - transpose(2, 0)*transpose(1, 1);
    adjugateContent[7] -= transpose(0, 0)*transpose(2, 1) - transpose(2, 0)*transpose(0, 1);
    adjugateContent[8] += transpose(0, 0)*transpose(1, 1) - transpose(1, 0)*transpose(0, 1);
    return Matrix3D(adjugateContent);
}

Matrix3D Matrix3D::invert() const {
    const double determinant = this->determinant();
    if (determinant == 0) throw std::invalid_argument("Matrix3D::Cannot invert, determinant is 0");
    Matrix3D adjugate = this->adjugate();
    Matrix3D inverse = Matrix3D(adjugate);
    for (size_t i = 0; i < 9; i++)
        inverse.content_[i] /= determinant;
    return inverse.transpose();
}

Matrix3D Matrix3D::identity() {
    return Matrix3D({1, 0, 0, 0, 1, 0, 0, 0, 1});
}

Matrix3D operator+(const Matrix3D &matrix3D_1, const Matrix3D &matrix3D_2) {
    std::vector<double> content_out = std::vector<double>(9, 0);
    for (size_t i = 0; i < 9; i++)
    {
        content_out[i] = matrix3D_1.content_[i] + matrix3D_2.content_[i];
    }
    return Matrix3D(content_out);
}

Matrix3D operator-(const Matrix3D &matrix3D_1, const Matrix3D &matrix3D_2) {
    std::vector<double> content_out = std::vector<double>(9, 0);
    for (size_t i = 0; i < 9; i++)
    {
        content_out[i] = matrix3D_1.content_[i] - matrix3D_2.content_[i];
    }
    return Matrix3D(content_out);
}

Matrix3D operator*(const Matrix3D &matrix3D, const double &multiplier) {
    std::vector<double> content_out = matrix3D.getContentAsStdVector();
    for (size_t i = 0; i < 9; i++)
    {
        content_out[i] = matrix3D.content_[i] * multiplier;
    }
    return Matrix3D(content_out);
}

Matrix3D operator*(const double &multiplier, const Matrix3D &matrix3D) {
    return operator*(matrix3D, multiplier);
}

Matrix3D operator*(const Matrix3D &matrix3D_1, const Matrix3D &matrix3D_2) {
    std::vector<double> content_1 = matrix3D_1.getContentAsStdVector();
    std::vector<double> content_2 = matrix3D_2.getContentAsStdVector();
    std::vector<double> content_out = std::vector<double>(9, 0);

    content_out[0] = content_1[0]*content_2[0] + content_1[1]*content_2[3] + content_1[2]*content_2[6];
    content_out[1] = content_1[0]*content_2[1] + content_1[1]*content_2[4] + content_1[2]*content_2[7];
    content_out[2] = content_1[0]*content_2[2] + content_1[1]*content_2[5] + content_1[2]*content_2[8];

    content_out[3] = content_1[3]*content_2[0] + content_1[4]*content_2[3] + content_1[5]*content_2[6];
    content_out[4] = content_1[3]*content_2[1] + content_1[4]*content_2[4] + content_1[5]*content_2[7];
    content_out[5] = content_1[3]*content_2[2] + content_1[4]*content_2[5] + content_1[5]*content_2[8];

    content_out[6] = content_1[6]*content_2[0] + content_1[7]*content_2[3] + content_1[8]*content_2[6];
    content_out[7] = content_1[6]*content_2[1] + content_1[7]*content_2[4] + content_1[8]*content_2[7];
    content_out[8] = content_1[6]*content_2[2] + content_1[7]*content_2[5] + content_1[8]*content_2[8];

    return Matrix3D(content_out);
}

bool operator==(const Matrix3D &matrix3D_1, const Matrix3D &matrix3D_2) {
    for (size_t i = 0; i < 9; i++)
    {
        if (abs(matrix3D_1.content_[i] - matrix3D_2.content_[i]) > epsilon) return false;
    }
    return true;
}

Vector3D operator*(const Matrix3D& matrix3D, const Vector3D& vecteur3D)
{
    float x = matrix3D(0, 0) * vecteur3D.get_x() + matrix3D(0, 1) * vecteur3D.get_y() + matrix3D(0, 2) * vecteur3D.get_z();
    float y = matrix3D(1, 0) * vecteur3D.get_x() + matrix3D(1, 1) * vecteur3D.get_y() + matrix3D(1, 2) * vecteur3D.get_z();
    float z = matrix3D(2, 0) * vecteur3D.get_x() + matrix3D(2, 1) * vecteur3D.get_y() + matrix3D(2, 2) * vecteur3D.get_z();
    return Vector3D(x, y, z);
   
}

std::ostream& operator<<(std::ostream& out, const Matrix3D& matrix3D) {
    out << matrix3D.content_[0] << " " << matrix3D.content_[1] << " " << matrix3D.content_[2] << std::endl;
    out << matrix3D.content_[3] << " " << matrix3D.content_[4] << " " << matrix3D.content_[5] << std::endl;
    out << matrix3D.content_[6] << " " << matrix3D.content_[7] << " " << matrix3D.content_[8] << std::endl;
    return out;
}
