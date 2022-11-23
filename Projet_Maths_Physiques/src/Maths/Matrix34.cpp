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

Matrix34 Matrix34::inverse() {
    std::vector<double> contentPadded = content;
    contentPadded.push_back(0);
    contentPadded.push_back(0);
    contentPadded.push_back(0);
    contentPadded.push_back(1);
    std::vector<double> inverseContent = Matrix4D(contentPadded).invert().getContentAsStdVector();
    std::vector<double> resultContent = {};
    for (std::vector<double>::iterator it=inverseContent.begin(); it!=inverseContent.begin()+12; ++it) {
        resultContent.push_back(*it);
    }
    return Matrix34(resultContent);
}

void Matrix34::setOrientationAndPosition(const Quaternion &orientation, const Vecteur3D &position) {
    std::vector<float> q = orientation.getContentAsStdVector();
    content = {
        1 - (2*q[2]*q[2] + 2*q[3]*q[3]),
        2*q[1]*q[2] - 2*q[3]*q[0],
        2*q[1]*q[3] + 2*q[2]*q[0],
        position.get_x(),

        2*q[1]*q[2] + 2*q[3]*q[0],
        1 - (2*q[1]*q[1] + 2*q[3]*q[3]),
        2*q[2]*q[3] - 2*q[1]*q[0],
        position.get_y(),
        
        2*q[1]*q[3] - 2*q[2]*q[0],
        2*q[2]*q[3] + 2*q[1]*q[0],
        1 - (2*q[1]*q[1] + 2*q[2]*q[2]),
        position.get_z()
    };
    return;    
}

Vecteur3D Matrix34::transformPosition(const Vecteur3D &position) {
    return *(this) * position;
}

Vecteur3D Matrix34::transformDirection(const Vecteur3D &direction) {
    std::vector<float> floatContent;
    /*std::transform(content.begin(), content.end(), floatContent.begin(), [](const double& element) {  //Ca fait des erreurs
        return static_cast<float>(element);
    });*/
    return Vecteur3D(
        direction.get_x() * (float)content[0] +
        direction.get_y() * (float)content[1] +
        direction.get_z() * (float)content[2],

        direction.get_x() * (float)content[4] +
        direction.get_y() * (float)content[5] +
        direction.get_z() * (float)content[6],

        direction.get_x() * (float)content[8] +
        direction.get_y() * (float)content[9] +
        direction.get_z() * (float)content[10]
    );
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

Matrix34 operator*(const Matrix34 &matrix_1, const Matrix34 &matrix_2) {
    std::vector<double> contentPadded_1 = matrix_1.content;
    contentPadded_1.push_back(0);
    contentPadded_1.push_back(0);
    contentPadded_1.push_back(0);
    contentPadded_1.push_back(1);
    std::vector<double> contentPadded_2 = matrix_2.content;
    contentPadded_2.push_back(0);
    contentPadded_2.push_back(0);
    contentPadded_2.push_back(0);
    contentPadded_2.push_back(1);
    std::vector<double> prodContent = (Matrix4D(contentPadded_1) * Matrix4D(contentPadded_2)).getContentAsStdVector();
    std::vector<double> resultContent = {};
    for (std::vector<double>::iterator it=prodContent.begin(); it!=prodContent.begin()+12; ++it) {
        resultContent.push_back(*it);
    }
    return Matrix34(resultContent);
}

Vecteur3D operator*(const Matrix34 &matrix, const Vecteur3D &vector) {
    std::vector<double> contentAsFloatVector = matrix.getContentAsStdVector();
    /*std::transform(matrix.content.begin(), matrix.content.end(), contentAsFloatVector.begin(), [](const double& nb) { ca fait crasher
        return static_cast<float>(nb);
    });*/

    return Vecteur3D(
        contentAsFloatVector[0] * vector.get_x() + contentAsFloatVector[1] * vector.get_y() + contentAsFloatVector[2] * vector.get_z() + contentAsFloatVector[3],
        contentAsFloatVector[4] * vector.get_x() + contentAsFloatVector[5] * vector.get_y() + contentAsFloatVector[6] * vector.get_z() + contentAsFloatVector[7],
        contentAsFloatVector[8] * vector.get_x() + contentAsFloatVector[9] * vector.get_y() + contentAsFloatVector[10] * vector.get_z() + contentAsFloatVector[11]
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


Matrix34 Matrix34::scaling(const Vecteur3D &scale)
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