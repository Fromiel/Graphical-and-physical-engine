#include "Maths/Matrix34.h"

Matrix34::Matrix34() {
    this->content = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    return;
}

Matrix34::Matrix34(const std::vector<double> &content) {
    if (content.size() != 12) throw std::invalid_argument("Matrix34::Provide content with size 12");
    this->content = content;
    return;
}

Matrix34::Matrix34(const Matrix34 &other) {
    this->content = other.content;
    return;
}

Matrix34::~Matrix34() {
    return;
}

std::vector<double> Matrix34::getContentAsStdVector() const {
    return content;
}

double Matrix34::operator()(const int &line, const int &column) const {
    if (line < 0 || line > 2 || column < 0 || column > 3) {
        throw std::invalid_argument("Matrix3D::Provide line in range 0-2 and column in range 0-3");
    }
    return content[Matrix34::columnCount * line + column];
}

double& Matrix34::operator()(const int line, const int column) {
    if (line < 0 || line > 2 || column < 0 || column > 3) {
        throw std::invalid_argument("Matrix3D::Provide line in range 0-2 and column in range 0-3");
    }
    return content[Matrix34::columnCount * line + column];
}

void Matrix34::operator=(const Matrix34 &matrix) {
    content = matrix.content;
    return;
}

Matrix34 Matrix34::operator+=(const Matrix34 &matrix) {
    std::transform(content.begin(), content.end(), matrix.content.begin(), content.begin(), std::plus<double>());
    return *this;
}

Matrix34 Matrix34::operator-=(const Matrix34 &matrix) {
    std::transform(content.begin(), content.end(), matrix.content.begin(), content.begin(), std::minus<double>());
    return *this;
}

Matrix34 operator+(const Matrix34 &matrix_1, const Matrix34 &matrix_2) {
    std::vector<double> content1 = matrix_1.getContentAsStdVector();
    std::vector<double> content2 = matrix_2.getContentAsStdVector();
    std::vector<double> content_out = std::vector<double>(Matrix34::columnCount * Matrix34::lineCount, 0);
    std::transform(content1.begin(), content1.end(), content2.begin(), content_out.begin(), std::plus<double>());
    return Matrix34(content_out);
}

Matrix34 operator-(const Matrix34 &matrix_1, const Matrix34 &matrix_2) {
    std::vector<double> content1 = matrix_1.getContentAsStdVector();
    std::vector<double> content2 = matrix_2.getContentAsStdVector();
    std::vector<double> content_out = std::vector<double>(Matrix34::columnCount * Matrix34::lineCount, 0);
    std::transform(content1.begin(), content1.end(), content2.begin(), content_out.begin(), std::minus<double>());
    return Matrix34(content_out);
}

Matrix34 operator*(const Matrix34 &matrix, const double &multiplier) {
    std::vector<double> content = matrix.getContentAsStdVector();
    std::transform(content.begin(), content.end(), content.begin(), [&multiplier](double &nb) {
        return nb * multiplier;
    });
    return Matrix34(content);
}

Matrix34 operator*(const double &multiplier, const Matrix34 &matrix) {
    return operator*(matrix, multiplier);
}

Vecteur3D operator*(const Matrix34 &matrix, const Vecteur3D &vector) {
    std::vector<double> content = std::vector<double>(9, 0);
    return Vecteur3D(
        matrix.content[0] * vector.get_x() + matrix.content[1] * vector.get_y() + matrix.content[2] * vector.get_z() + matrix.content[3],
        matrix.content[4] * vector.get_x() + matrix.content[5] * vector.get_y() + matrix.content[6] * vector.get_z() + matrix.content[7],
        matrix.content[8] * vector.get_x() + matrix.content[9] * vector.get_y() + matrix.content[10] * vector.get_z() + matrix.content[11]
    );
}

bool operator==(const Matrix34 &matrix_1, const Matrix34 &matrix_2) {
    return matrix_1.getContentAsStdVector() == matrix_2.getContentAsStdVector();
}

std::ostream &operator<<(std::ostream &out, const Matrix34 &matrix) {
    for (int i=0; i<matrix.content.size()-1; ++i) out << matrix.content[i] << ", ";
    out << matrix.content[matrix.content.size()-1];
    return out;
}
