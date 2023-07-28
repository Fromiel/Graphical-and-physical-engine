#include "Maths/Matrix34.h"

#include <algorithm>
#include <functional>

const float epsilon = 0.00001f;

Matrix34::Matrix34() : content_{} {}

Matrix34::Matrix34(const std::vector<double> &content) {
    if (content.size() != 12) throw std::invalid_argument("Matrix34::Provide content with size 12");

    for (size_t i = 0; i < 12; i++)
        content_[i] = content[i];

    return;
}

std::vector<double> Matrix34::getContentAsStdVector() const {
    return std::vector<double>(content_, content_ + 12);
}


// inv( M v )  = ( inv(M) -v )
//    ( 0 1 )    (	 0    1  )
Matrix34 Matrix34::invert() {
    Matrix3D M = Matrix3D({
        content_[0], content_[1], content_[2],
        content_[4], content_[5], content_[6],
        content_[8], content_[9], content_[10]
    });

    const double determinant = M.determinant();
    if (determinant == 0) throw std::invalid_argument("Matrix34::Cannot invert, determinant is 0");

    Matrix3D invM = M.invert();

    Matrix34 inverse({invM(0, 0), invM(0, 1), invM(0, 2), -content_[3],
					  invM(1, 0), invM(1, 1), invM(1, 2), -content_[7],
					  invM(2, 0), invM(2, 1), invM(2, 2), -content_[11]
    });

    return inverse;
}

void Matrix34::setOrientationAndPosition(const Quaternion &orientation, const Vector3D &position) {
    std::vector<float> q = orientation.getContentAsStdVector();
    content_[0] = 1 - (2 * q[2] * q[2] + 2 * q[3] * q[3]);
    content_[1] = 2 * q[1] * q[2] - 2 * q[3] * q[0];
    content_[2] = 2 * q[1] * q[3] + 2 * q[2] * q[0];
    content_[3] = position.get_x();

    content_[4] = 2 * q[1] * q[2] + 2 * q[3] * q[0];
    content_[5] = 1 - (2 * q[1] * q[1] + 2 * q[3] * q[3]);
    content_[6] = 2 * q[2] * q[3] - 2 * q[1] * q[0];
    content_[7] = position.get_y();

    content_[8] = 2 * q[1] * q[3] - 2 * q[2] * q[0];
    content_[9] = 2 * q[2] * q[3] + 2 * q[1] * q[0];
    content_[10] = 1 - (2 * q[1] * q[1] + 2 * q[2] * q[2]);
    content_[11] = position.get_z();
    
    return;    
}

Vector3D Matrix34::transformPosition(const Vector3D &position) {
    return *(this) * position;
}

Vector3D Matrix34::transformDirection(const Vector3D &direction) {
    std::vector<float> floatContent;

    return Vector3D(
        direction.get_x() * (float)content_[0] +
        direction.get_y() * (float)content_[1] +
        direction.get_z() * (float)content_[2],

        direction.get_x() * (float)content_[4] +
        direction.get_y() * (float)content_[5] +
        direction.get_z() * (float)content_[6],

        direction.get_x() * (float)content_[8] +
        direction.get_y() * (float)content_[9] +
        direction.get_z() * (float)content_[10]
    );
}

double Matrix34::operator()(const int &line, const int &column) const {
    if (line < 0 || line > 2 || column < 0 || column > 3) {
        throw std::invalid_argument("Matrix3D::Provide line in range 0-2 and column in range 0-3");
    }
    return content_[Matrix34::columnCount * line + column];
}

double& Matrix34::operator()(const int line, const int column) {
    if (line < 0 || line > 2 || column < 0 || column > 3) {
        throw std::invalid_argument("Matrix3D::Provide line in range 0-2 and column in range 0-3");
    }
    return content_[Matrix34::columnCount * line + column];
}

void Matrix34::operator=(const Matrix34 &matrix) {
    for (size_t i = 0; i < 12; i++)
        content_[i] = matrix.content_[i];;
    return;;
}

Matrix34 Matrix34::operator+=(const Matrix34 &matrix) {
    for (size_t i = 0; i < 12; i++)
        content_[i] += matrix.content_[i];

    return *this;
}

Matrix34 Matrix34::operator-=(const Matrix34 &matrix) {
    for (size_t i = 0; i < 12; i++)
        content_[i] -= matrix.content_[i];

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

Matrix34 operator*(const Matrix34 &matrix_1, const Matrix34 &matrix_2) {
    std::vector<double> content;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++)
        {
            int b = 0; //if we are at the last column, b equal 1 else b equal 0
            if(j == 3)
			    b = 1;
            content.push_back(matrix_1(i, 0) * matrix_2(0, j) + matrix_1(i, 1) * matrix_2(1, j) + matrix_1(i, 2) * matrix_2(2, j) + matrix_1(i, 3) * b);
        }
	}

    return Matrix34(content);
}

Vector3D operator*(const Matrix34 &matrix, const Vector3D &vector) {
    std::vector<double> contentAsVector = matrix.getContentAsStdVector();

    return Vector3D(
        contentAsVector[0] * vector.get_x() + contentAsVector[1] * vector.get_y() + contentAsVector[2] * vector.get_z() + contentAsVector[3],
        contentAsVector[4] * vector.get_x() + contentAsVector[5] * vector.get_y() + contentAsVector[6] * vector.get_z() + contentAsVector[7],
        contentAsVector[8] * vector.get_x() + contentAsVector[9] * vector.get_y() + contentAsVector[10] * vector.get_z() + contentAsVector[11]
    );
}

bool operator==(const Matrix34 &matrix_1, const Matrix34 &matrix_2) {
    for (size_t i = 0; i < 12; i++)
    {
        if (abs(matrix_1.content_[i] - matrix_2.content_[i]) > epsilon) return false;
    }
    return true;
}

std::ostream &operator<<(std::ostream &out, const Matrix34 &matrix) {
    for (int i=0; i < 11; ++i) out << matrix.content_[i] << ", ";
    out << matrix.content_[11] << std::endl;
    return out;
}


Matrix34 Matrix34::scaling(const Vector3D &scale)
{
    std::vector<double> elements = { scale.get_x(), 0, 0, 0, 0, scale.get_y(), 0, 0, 0, 0, scale.get_z(), 0};
    Matrix34 res(elements);
    return res;
}


void Matrix34::toFloatArray(float* arr)
{
    std::vector<double> content = getContentAsStdVector();
    std::vector<double> contentModif = {content[0], content[4], content[8], 0,content[1], content[5], content[9], 0, content[2], content[6], content[10], 0, content[3], content[7], content[11], 1};
    std::copy(contentModif.begin(), contentModif.end(), arr);
}


Matrix4D operator*(const Matrix4D& matrix4D, const Matrix34& matrix34)
{
    std::vector<double> content = matrix34.getContentAsStdVector();
    content.push_back(0);
    content.push_back(0);
    content.push_back(0);
    content.push_back(1);
    return matrix4D * Matrix4D(content);
}

Matrix4D operator*(const Matrix34& matrix34, const Matrix4D& matrix4D)
{
    std::vector<double> content = matrix34.getContentAsStdVector();
    content.push_back(0);
    content.push_back(0);
    content.push_back(0);
    content.push_back(1);
    return Matrix4D(content) * matrix4D;
}

Matrix3D operator*(const Matrix34& matrix34, const Matrix3D& matrix3) {
    std::vector<double> content = { matrix34(0,0), matrix34(0,1), matrix34(0,2), matrix34(1,0), matrix34(1,1), matrix34(1,2), matrix34(2,0), matrix34(2,1), matrix34(2,2) };
    Matrix3D newMat(content);
    return newMat * matrix3;
}

Matrix3D operator*(const Matrix3D& matrix3, const Matrix34& matrix34) {
    std::vector<double> content = { matrix34(0,0), matrix34(0,1), matrix34(0,2), matrix34(1,0), matrix34(1,1), matrix34(1,2), matrix34(2,0), matrix34(2,1), matrix34(2,2) };
    Matrix3D newMat(content);
    return matrix3 * newMat;
}