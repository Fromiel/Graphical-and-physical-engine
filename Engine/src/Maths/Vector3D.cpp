#include "Maths/Vector3D.h"
#include <math.h>
#include <cmath>

const float epsilon = 0.0001;

Vector3D::Vector3D(float x, float y, float z) : x_(x), y_(y), z_(z) {}

float Vector3D::norm() const{
    return static_cast<float>(sqrt(norm_squared()));
}

float Vector3D::norm_squared() const {
    return static_cast<float>(pow(x_, 2) + pow(y_, 2) + pow(z_, 2));
}

Vector3D Vector3D::normalized() {
    float norm_vect = norm();
    if (norm_vect == 0) {
        throw std::logic_error("ERROR : Can't normalize the null vector");
    }
    x_ /= norm_vect;
    y_ /= norm_vect;
    z_ /= norm_vect;
    return *this;
}

Vector3D Vector3D::operator*=(const float& scalar) {
    x_ *= scalar;
    y_ *= scalar;
    z_ *= scalar;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Vector3D& vect) {                             // Print : [ x; y; z ]
    out << "[ " << vect.x_ << "; " << vect.y_ << "; " << vect.z_ << " ]";
    return out;
}

Vector3D operator+(const Vector3D &vect1, const Vector3D &vect2) {
    Vector3D res(vect1.x_ + vect2.x_, vect1.y_ + vect2.y_, vect1.z_ + vect2.z_);
    return res;
}

Vector3D operator-(const Vector3D &vect1, const Vector3D &vect2) {
    Vector3D res(vect1.x_ - vect2.x_, vect1.y_ - vect2.y_, vect1.z_ - vect2.z_);
    return res;
}

Vector3D operator*(const Vector3D &vect1, const Vector3D &vect2) {
    Vector3D res(vect1.x_ * vect2.x_, vect1.y_ * vect2.y_, vect1.z_ * vect2.z_);
    return res;
}

float Vector3D::scalar_product(const Vector3D &vect1, const Vector3D &vect2) {
    float res;
    res = (vect1.x_ * vect2.x_) + (vect1.y_ * vect2.y_) + (vect1.z_ * vect2.z_);
    return res;
}

Vector3D Vector3D::vectorial_product(const Vector3D &vect1, const Vector3D &vect2) {
    float x = vect1.y_ * vect2.z_ - vect1.z_ * vect2.y_;
    float y = vect1.z_ * vect2.x_ - vect1.x_ * vect2.z_;
    float z = vect1.x_ * vect2.y_ - vect1.y_ * vect2.x_;
    Vector3D res(x, y, z);
    return res;
}

Vector3D operator*(const float d, const Vector3D& v) {
    float x = v.x_ * d;
    float y = v.y_ * d;
    float z = v.z_ * d;
    Vector3D res(x, y, z);
    return res;   
}

Vector3D operator*(const Vector3D& v, const float d) { return d * v; }

float Vector3D::distance(const Vector3D& vect1, const Vector3D& vect2) 
{
    float dist_x = static_cast<float>(pow(vect1.x_ - vect2.x_, 2));
    float dist_y = static_cast<float>(pow(vect1.y_ - vect2.y_, 2));
    float dist_z = static_cast<float>(pow(vect1.z_ - vect2.z_, 2));
    return sqrt(dist_x + dist_y + dist_z);
}


float Vector3D::maxValue() const
{
    float m = x_;
    if (m < y_)
        m = y_;
    if (m < z_)
        m = z_;
    return m;
}


bool operator==(const Vector3D& v1, const Vector3D& v2)
{
	return (fabs(v1.x_ - v2.x_) < epsilon) && (fabs(v1.y_ - v2.y_) < epsilon) && (fabs(v1.z_ - v2.z_) < epsilon);
}