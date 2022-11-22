#include "Maths/Matrix4D.h"

Matrix4D::Matrix4D()
{
    std::vector<double> content = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    _content = content;
}


Matrix4D::Matrix4D(const std::vector<double>& content) : _content(content) {
	if (_content.size() != 16) throw std::invalid_argument("Matrix3D::Provide content with size 16");
}

Matrix4D::Matrix4D(const Matrix4D& matrix4D) {
	_content = matrix4D._content;
}

std::vector<double> Matrix4D::getContentAsStdVector() const {
	return _content;
}

double Matrix4D::operator() (int line, int column) const {
	if (line < 0 || line > 3 || column < 0 || column > 3) {
		throw std::out_of_range("Matrix4D::Provide line and column between 0 and 3 include");
	}
	return _content[Matrix4D::columnCount * line + column];
}

double& Matrix4D::operator() (int line, int column) {
    if (line < 0 || line > 3 || column < 0 || column > 3) {
        throw std::out_of_range("Matrix4D::Provide line and column between 0 and 3 include");
    }
    return _content[Matrix4D::columnCount * line + column];
}

void Matrix4D::operator=(const Matrix4D& matrix4D) {
	_content = matrix4D._content;
}

Matrix4D Matrix4D::operator+=(const Matrix4D& matrix4D) {
	std::transform(_content.begin(), _content.end(), matrix4D._content.begin(), _content.begin(), std::plus<double>());
    return *this;
}

Matrix4D Matrix4D::operator-=(const Matrix4D& matrix4D) {
	std::transform(_content.begin(), _content.end(), matrix4D._content.begin(), _content.begin(), std::minus<double>());
    return *this;
}

Matrix4D Matrix4D::transpose() const {
	Matrix4D res = Matrix4D({
		_content[0], _content[4], _content[8], _content[12],
		_content[1], _content[5], _content[9], _content[13],
		_content[2], _content[6], _content[10], _content[14],
		_content[3], _content[7], _content[11], _content[15]
	});
	return res;
}

Matrix4D Matrix4D::invert() const
    {
        std::vector<double> m = _content;
        double inv[16], det;
        int i;

        inv[0] = m[5] * m[10] * m[15] -
            m[5] * m[11] * m[14] -
            m[9] * m[6] * m[15] +
            m[9] * m[7] * m[14] +
            m[13] * m[6] * m[11] -
            m[13] * m[7] * m[10];

        inv[4] = -m[4] * m[10] * m[15] +
            m[4] * m[11] * m[14] +
            m[8] * m[6] * m[15] -
            m[8] * m[7] * m[14] -
            m[12] * m[6] * m[11] +
            m[12] * m[7] * m[10];

        inv[8] = m[4] * m[9] * m[15] -
            m[4] * m[11] * m[13] -
            m[8] * m[5] * m[15] +
            m[8] * m[7] * m[13] +
            m[12] * m[5] * m[11] -
            m[12] * m[7] * m[9];

        inv[12] = -m[4] * m[9] * m[14] +
            m[4] * m[10] * m[13] +
            m[8] * m[5] * m[14] -
            m[8] * m[6] * m[13] -
            m[12] * m[5] * m[10] +
            m[12] * m[6] * m[9];

        inv[1] = -m[1] * m[10] * m[15] +
            m[1] * m[11] * m[14] +
            m[9] * m[2] * m[15] -
            m[9] * m[3] * m[14] -
            m[13] * m[2] * m[11] +
            m[13] * m[3] * m[10];

        inv[5] = m[0] * m[10] * m[15] -
            m[0] * m[11] * m[14] -
            m[8] * m[2] * m[15] +
            m[8] * m[3] * m[14] +
            m[12] * m[2] * m[11] -
            m[12] * m[3] * m[10];

        inv[9] = -m[0] * m[9] * m[15] +
            m[0] * m[11] * m[13] +
            m[8] * m[1] * m[15] -
            m[8] * m[3] * m[13] -
            m[12] * m[1] * m[11] +
            m[12] * m[3] * m[9];

        inv[13] = m[0] * m[9] * m[14] -
            m[0] * m[10] * m[13] -
            m[8] * m[1] * m[14] +
            m[8] * m[2] * m[13] +
            m[12] * m[1] * m[10] -
            m[12] * m[2] * m[9];

        inv[2] = m[1] * m[6] * m[15] -
            m[1] * m[7] * m[14] -
            m[5] * m[2] * m[15] +
            m[5] * m[3] * m[14] +
            m[13] * m[2] * m[7] -
            m[13] * m[3] * m[6];

        inv[6] = -m[0] * m[6] * m[15] +
            m[0] * m[7] * m[14] +
            m[4] * m[2] * m[15] -
            m[4] * m[3] * m[14] -
            m[12] * m[2] * m[7] +
            m[12] * m[3] * m[6];

        inv[10] = m[0] * m[5] * m[15] -
            m[0] * m[7] * m[13] -
            m[4] * m[1] * m[15] +
            m[4] * m[3] * m[13] +
            m[12] * m[1] * m[7] -
            m[12] * m[3] * m[5];

        inv[14] = -m[0] * m[5] * m[14] +
            m[0] * m[6] * m[13] +
            m[4] * m[1] * m[14] -
            m[4] * m[2] * m[13] -
            m[12] * m[1] * m[6] +
            m[12] * m[2] * m[5];

        inv[3] = -m[1] * m[6] * m[11] +
            m[1] * m[7] * m[10] +
            m[5] * m[2] * m[11] -
            m[5] * m[3] * m[10] -
            m[9] * m[2] * m[7] +
            m[9] * m[3] * m[6];

        inv[7] = m[0] * m[6] * m[11] -
            m[0] * m[7] * m[10] -
            m[4] * m[2] * m[11] +
            m[4] * m[3] * m[10] +
            m[8] * m[2] * m[7] -
            m[8] * m[3] * m[6];

        inv[11] = -m[0] * m[5] * m[11] +
            m[0] * m[7] * m[9] +
            m[4] * m[1] * m[11] -
            m[4] * m[3] * m[9] -
            m[8] * m[1] * m[7] +
            m[8] * m[3] * m[5];

        inv[15] = m[0] * m[5] * m[10] -
            m[0] * m[6] * m[9] -
            m[4] * m[1] * m[10] +
            m[4] * m[2] * m[9] +
            m[8] * m[1] * m[6] -
            m[8] * m[2] * m[5];

        det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

        //std::cout << "DEBUG : det = " << det << std::endl;

        if (det == 0) {
            //throw "Matrice non inversible";

            std::cout << "Matrice non inversible" << std::endl;
            //throw std::logic_error("Matrice non inversible");
            return Matrix4D(); //should throw but throw not working
        }
            
        det = 1.0 / det;

        std::vector<double> invOut;

        for (i = 0; i < 16; i++)
            invOut.push_back(inv[i] * det);

        return Matrix4D(invOut);
}

Matrix4D Matrix4D::identity() {
    Matrix4D res({ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 });
    return res;
}

Matrix4D Matrix4D::translation(const Vecteur3D &vect) {
    std::vector<double> elements = { 1, 0, 0, vect.get_x(), 0, 1, 0, vect.get_y(), 0, 0, 1, vect.get_z(), 0, 0, 0, 1 };
    Matrix4D res(elements);
    return res;
}

Matrix4D Matrix4D::scaling(const Vecteur3D& vect) {
    std::vector<double> elements = { vect.get_x(), 0, 0, 0, 0, vect.get_y(), 0, 0, 0, 0, vect.get_z(), 0, 0, 0, 0, 1 };
    Matrix4D res(elements);
    return res;
}

void Matrix4D::toFloatArray(float arr[])
{
    std::vector<double> content = this->transpose().getContentAsStdVector();
    std::copy(content.begin(), content.end(), arr);
}

// static Matrix4D Matrix4D::rotation(Vecteur3D &vect){}

Matrix4D operator+(const Matrix4D& matrix4D_1, const Matrix4D& matrix4D_2) {
    Matrix4D res;
    for (int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++)
            res(i, j) = matrix4D_1(i, j) + matrix4D_2(i, j);
    }
    return res;
}

Matrix4D operator-(const Matrix4D& matrix4D_1, const Matrix4D& matrix4D_2) {
    Matrix4D res;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            res(i, j) = matrix4D_1(i, j) - matrix4D_2(i, j);
    }
    return res;
}

Matrix4D operator*(const Matrix4D& matrix4D, const double &scalar) {
    Matrix4D res;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            res(i, j) = matrix4D(i, j) * scalar;
    }
    return res;
}

Matrix4D operator*(const double &scalar, const Matrix4D& matrix4D) {
    return matrix4D * scalar;
}

Matrix4D operator*(const Matrix4D& matrix4D_1, const Matrix4D& matrix4D_2) {
    std::vector<double> content_1 = matrix4D_1.getContentAsStdVector();
    std::vector<double> content_2 = matrix4D_2.getContentAsStdVector();
    std::vector<double> content_out = std::vector<double>(16, 0);

    content_out[0] = content_1[0] * content_2[0] + content_1[1] * content_2[4] + content_1[2] * content_2[8] + content_1[3] * content_2[12];
    content_out[1] = content_1[0] * content_2[1] + content_1[1] * content_2[5] + content_1[2] * content_2[9] + content_1[3] * content_2[13];
    content_out[2] = content_1[0] * content_2[2] + content_1[1] * content_2[6] + content_1[2] * content_2[10] + content_1[3] * content_2[14];
    content_out[3] = content_1[0] * content_2[3] + content_1[1] * content_2[7] + content_1[2] * content_2[11] + content_1[3] * content_2[15];
    
    content_out[4] = content_1[4] * content_2[0] + content_1[5] * content_2[4] + content_1[6] * content_2[8] + content_1[7] * content_2[12];
    content_out[5] = content_1[4] * content_2[1] + content_1[5] * content_2[5] + content_1[6] * content_2[9] + content_1[7] * content_2[13];
    content_out[6] = content_1[4] * content_2[2] + content_1[5] * content_2[6] + content_1[6] * content_2[10] + content_1[7] * content_2[14];
    content_out[7] = content_1[4] * content_2[3] + content_1[5] * content_2[7] + content_1[6] * content_2[11] + content_1[7] * content_2[15];

    content_out[8] = content_1[8] * content_2[0] + content_1[9] * content_2[4] + content_1[10] * content_2[8] + content_1[11] * content_2[12];
    content_out[9] = content_1[8] * content_2[1] + content_1[9] * content_2[5] + content_1[10] * content_2[9] + content_1[11] * content_2[13];
    content_out[10] = content_1[8] * content_2[2] + content_1[9] * content_2[6] + content_1[10] * content_2[10] + content_1[11] * content_2[14];
    content_out[11] = content_1[8] * content_2[3] + content_1[9] * content_2[7] + content_1[10] * content_2[11] + content_1[11] * content_2[15];

    content_out[12] = content_1[12] * content_2[0] + content_1[13] * content_2[4] + content_1[14] * content_2[8] + content_1[15] * content_2[12];
    content_out[13] = content_1[12] * content_2[1] + content_1[13] * content_2[5] + content_1[14] * content_2[9] + content_1[15] * content_2[13];
    content_out[14] = content_1[12] * content_2[2] + content_1[13] * content_2[6] + content_1[14] * content_2[10] + content_1[15] * content_2[14];
    content_out[15] = content_1[12] * content_2[3] + content_1[13] * content_2[7] + content_1[14] * content_2[11] + content_1[15] * content_2[15];

    return Matrix4D(content_out);
}

bool operator==(const Matrix4D& matrix4D_1, const Matrix4D& matrix4D_2) {
    return matrix4D_1.getContentAsStdVector() == matrix4D_2.getContentAsStdVector();
}

std::ostream& operator<<(std::ostream& out, const Matrix4D& matrix4D) {
    std::vector<double> content = matrix4D.getContentAsStdVector();

    out << "[ " << content[0] << ", " << content[1] << ", " << content[2] << ", " << content[3] << " ]" << std::endl;
    out << "[ " << content[4] << ", " << content[5] << ", " << content[6] << ", " << content[7] << " ]" << std::endl;
    out << "[ " << content[8] << ", " << content[9] << ", " << content[10] << ", " << content[11] << " ]" << std::endl;
    out << "[ " << content[12] << ", " << content[13] << ", " << content[14] << ", " << content[15] << " ]" << std::endl;
    return out;
}

