#include "Maths/Quaternion.h"

#include <cmath>

Quaternion::Quaternion(float w, float x, float y, float z, bool shouldNormalize) : w_(w), x_(x), y_(y), z_(z) {
    //if (w == x && x == y && y == z && z == 0) w = 1; //Don't know why someone did that before
    if (shouldNormalize) normalize();
    return;
}

Quaternion::Quaternion(const Vector3D &orientation)
{
    double cr = cos(orientation.get_x() * 0.5);
    double sr = sin(orientation.get_x() * 0.5);
    double cp = cos(orientation.get_y() * 0.5);
    double sp = sin(orientation.get_y() * 0.5);
    double cy = cos(orientation.get_z() * 0.5);
    double sy = sin(orientation.get_z() * 0.5);

    w_ = cr * cp * cy + sr * sp * sy;
    x_ = sr * cp * cy - cr * sp * sy;
    y_ = cr * sp * cy + sr * cp * sy;
    z_ = cr * cp * sy - sr * sp * cy;
}


void Quaternion::normalize() {
    float magnitude = static_cast<float>(sqrt(pow(w_, 2) + pow(x_, 2) + pow(y_, 2) + pow(z_, 2)));
    if (magnitude != 0) {
        w_ /= magnitude;
        x_ /= magnitude;
        y_ /= magnitude;
        z_ /= magnitude;
    }
    else {
        w_ = 0;
        x_ = 0;
        y_ = 0;
        z_ = 0;
    }
    
    return;
}

void Quaternion::rotateByVector(const Vector3D &vector) {
    Quaternion rotation = Quaternion(0, vector.get_x(), vector.get_y(), vector.get_z(), false);
    Quaternion result = (*this) * rotation;
    w_ = result.w_;
    x_ = result.x_;
    y_ = result.y_;
    z_ = result.z_;
    normalize();
    return;
}

void Quaternion::updateByAngularVelocity(const Vector3D &vector, float duration) {
    Quaternion rotation = Quaternion(0, vector.get_x() * duration, vector.get_y() * duration, vector.get_z() * duration, false);
    Quaternion result = rotation * (*this);

    w_ += result.w_ * 0.5f;
    x_ += result.x_ * 0.5f;
    y_ += result.y_ * 0.5f;
    z_ += result.z_ * 0.5f;

    normalize();
    return;
}

std::vector<float> Quaternion::getContentAsStdVector() const {
    return std::vector<float>({w_, x_, y_, z_});
}

void Quaternion::operator=(const Quaternion &other) {
    w_ = other.w_;
    x_ = other.x_;
    y_ = other.y_;
    z_ = other.z_;
    return;
}

Quaternion Quaternion::operator*=(const Quaternion &other) {
    Quaternion result = (*this) * other;
    w_ = result.w_;
    x_ = result.x_;
    y_ = result.y_;
    z_ = result.z_;
    return *this;
}

Quaternion operator*(const Quaternion &q1, const Quaternion &q2) {
    float a1 = q1.w_;
    float b1 = q1.x_;
    float c1 = q1.y_;
    float d1 = q1.z_;

    float a2 = q2.w_;
    float b2 = q2.x_;
    float c2 = q2.y_;
    float d2 = q2.z_;

    //std::cout << "\n q1*q2" << std::endl;
    //std::cout << "q1 = " << q1 << " q2 = " << q2 << std::endl;

    Quaternion result;
    result.w_ = a1*a2 - b1*b2 - c1*c2 - d1*d2;
    result.x_ = a1*b2 + b1*a2 + c1*d2 - d1*c2;
    result.y_ = a1*c2 - b1*d2 + c1*a2 + d1*b2;
    result.z_ = a1*d2 + b1*c2 - c1*b2 + d1*a2;
    //std::cout << "result = " << result << std::endl;
    //result.normalize();
    //std::cout << "result normalize = " << result << std::endl;

    return result;
}

std::ostream &operator<<(std::ostream &out, const Quaternion &quaternion) {
    return out << "(" << quaternion.w_ << ", " << quaternion.x_ << ", " << quaternion.y_ << ", " << quaternion.z_ << ")";
}
