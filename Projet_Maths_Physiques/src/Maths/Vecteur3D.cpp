//
// Created by jules on 07/09/2022.
//

#include "Maths/Vecteur3D.h"
#include <math.h>
using namespace std;

Vecteur3D::Vecteur3D(float x, float y, float z) : _x(x), _y(y), _z(z)
{}

Vecteur3D::Vecteur3D(const Vecteur3D& vect) : _x(vect.get_x()), _y(vect.get_y()), _z(vect.get_z())
{}

float Vecteur3D::norm(){
    return static_cast<float>(sqrt(pow(_x,2)+pow(_y,2)+pow(_z,2)));
}

float Vecteur3D::norm_squared() {
    return static_cast<float>(pow(norm(), 2));
}

Vecteur3D Vecteur3D::normalized() {
    float norm_vect = norm();
    if (norm_vect == 0) {
        return *this;
    }
    _x = _x / norm_vect;
    _y = _y / norm_vect;
    _z = _z / norm_vect;
    return *this;
}

Vecteur3D Vecteur3D::scalar_multiplication(float scalar) {
    _x = scalar * _x;
    _y = scalar * _y;
    _z = scalar * _z;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Vecteur3D& vect) {                             // Affichage sous la forme [ a; b; c ]
    out << "[ " << vect.get_x() << "; " << vect.get_y() << "; " << vect.get_z() << " ]";
    return out;
}

Vecteur3D operator+(const Vecteur3D &vect1, const Vecteur3D &vect2) {
    Vecteur3D res(vect1.get_x() + vect2.get_x(), vect1.get_y() + vect2.get_y(), vect1.get_z() + vect2.get_z());
    return res;
}

Vecteur3D operator-(const Vecteur3D &vect1, const Vecteur3D &vect2) {
    Vecteur3D res(vect1.get_x() - vect2.get_x(), vect1.get_y() - vect2.get_y(), vect1.get_z() - vect2.get_z());
    return res;
}

Vecteur3D operator*(const Vecteur3D &vect1, const Vecteur3D &vect2) {
    Vecteur3D res(vect1.get_x() * vect2.get_x(), vect1.get_y() * vect2.get_y(), vect1.get_z() * vect2.get_z());
    return res;
}

float scalar_product(const Vecteur3D &vect1, const Vecteur3D &vect2) {
    float res;
    res = (vect1.get_x() * vect2.get_x()) + (vect1.get_y() * vect2.get_y()) + (vect1.get_z() * vect2.get_z());
    return res;
}

Vecteur3D vectorial_product(const Vecteur3D &vect1, const Vecteur3D &vect2) {
    float x = vect1.get_y() * vect2.get_z() - vect1.get_z() * vect2.get_y();
    float y = vect1.get_z() * vect2.get_x() - vect1.get_x() * vect2.get_z();
    float z = vect1.get_x() * vect2.get_y() - vect1.get_y() * vect2.get_x();
    Vecteur3D res(x, y, z);
    return res;
}

Vecteur3D operator*(const float d, const Vecteur3D& v) {
    float x = v.get_x() * d;
    float y = v.get_y() * d;
    float z = v.get_z() * d;
    Vecteur3D res(x, y, z);
    return res;   
}

Vecteur3D operator*(const Vecteur3D& v, const float d) { return d * v; }

float distance(const Vecteur3D& vect1, const Vecteur3D& vect2) {
    float dist_x = static_cast<float>(pow(vect1.get_x() - vect2.get_x(), 2));
    float dist_y = static_cast<float>(pow(vect1.get_y() - vect2.get_y(), 2));
    float dist_z = static_cast<float>(pow(vect1.get_z() - vect2.get_z(), 2));
    return sqrt(dist_x + dist_y + dist_z);
}
