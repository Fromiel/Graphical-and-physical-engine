#include "Matrix3D.h"

Matrix3D::Matrix3D() {
    this->content = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    return;
}

Matrix3D::Matrix3D(const std::vector<double> &content) {
    if (content.size() != 9) throw std::invalid_argument("Matrix3D::Provide content with size 9");
    this->content = content;
    return;
}

Matrix3D::Matrix3D(const Matrix3D &matrix3D) {
    this->content = matrix3D.content;
    return;
}

std::vector<double> Matrix3D::getContentAsStdVector() const {
    return content;
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
    return content[Matrix3D::columnCount * line + column];
}

double& Matrix3D::operator()(const int line, const int column) {
    if (line < 0 || line > 2 || column < 0 || column > 2) {
        throw std::invalid_argument("Matrix3D::Provide line and column inferior to 3");
    }
    return content[Matrix3D::columnCount * line + column];
}

void Matrix3D::operator=(const Matrix3D &matrix3D) {
    content = matrix3D.content;
    return;
}

Matrix3D Matrix3D::operator+=(const Matrix3D &matrix3D) {
    std::transform(content.begin(), content.end(), matrix3D.content.begin(), content.begin(), std::plus<double>());
    return *this;
}

Matrix3D Matrix3D::operator-=(const Matrix3D &matrix3D) {
    std::transform(content.begin(), content.end(), matrix3D.content.begin(), content.begin(), std::minus<double>());
    return *this;
}

double Matrix3D::determinant() const {
    return 
        content[0] * (content[4]*content[8] - content[5]*content[7]) -
        content[1] * (content[3]*content[8] - content[5]*content[6]) +
        content[2] * (content[3]*content[7] - content[4]*content[6])
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
        content[0], content[3], content[6],
        content[1], content[4], content[7],
        content[2], content[5], content[8]
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
    std::transform(inverse.content.begin(), inverse.content.end(), inverse.content.begin(), [&determinant](double &nb) {
        return nb / determinant;
    });
    return inverse.transpose();
}

Matrix3D Matrix3D::identity() {
    return Matrix3D({1, 0, 0, 0, 1, 0, 0, 0, 1});
}

Matrix3D operator+(const Matrix3D &matrix3D_1, const Matrix3D &matrix3D_2) {
    std::vector<double> content1 = matrix3D_1.getContentAsStdVector();
    std::vector<double> content2 = matrix3D_2.getContentAsStdVector();
    std::vector<double> content_out = std::vector<double>(Matrix3D::columnCount * Matrix3D::lineCount, 0);
    std::transform(content1.begin(), content1.end(), content2.begin(), content_out.begin(), std::plus<double>());
    return Matrix3D(content_out);
}

Matrix3D operator-(const Matrix3D &matrix3D_1, const Matrix3D &matrix3D_2) {
    std::vector<double> content1 = matrix3D_1.getContentAsStdVector();
    std::vector<double> content2 = matrix3D_2.getContentAsStdVector();
    std::vector<double> content_out = std::vector<double>(Matrix3D::columnCount * Matrix3D::lineCount, 0);
    std::transform(content1.begin(), content1.end(), content2.begin(), content_out.begin(), std::minus<double>());
    return Matrix3D(content_out);
}

Matrix3D operator*(const Matrix3D &matrix3D, const double &multiplier) {
    std::vector<double> content = matrix3D.getContentAsStdVector();
    std::transform(content.begin(), content.end(), content.begin(), [&multiplier](double &nb) {
        return nb * multiplier;
    });
    return Matrix3D(content);
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
    return matrix3D_1.getContentAsStdVector() == matrix3D_2.getContentAsStdVector();
}

std::ostream &operator<<(std::ostream &out, const Matrix3D &matrix3D) {
    std::vector<double> content = matrix3D.getContentAsStdVector();
    out << content[0] << " " << content[1] << " " << content[2] << std::endl;
    out << content[3] << " " << content[4] << " " << content[5] << std::endl;
    out << content[6] << " " << content[7] << " " << content[8] << std::endl;
    return out;
}
