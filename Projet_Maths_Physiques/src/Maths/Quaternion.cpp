#include "Maths/Quaternion.h"

Quaternion::Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {
    normalize();
    return;
};

Quaternion::Quaternion(const Quaternion &other) {
    this->w = other.w;
    this->x = other.x;
    this->y = other.y;
    this->w = other.w;
    return;
}

Quaternion::~Quaternion() {
    return;
}

void Quaternion::normalize() {
    float magnitude = sqrt(pow(w, 2) + pow(x, 2) + pow(y, 2) + pow(z, 2));
    w /= magnitude;
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
    return;
}

void Quaternion::rotateByVector(const Vecteur3D &vector) {
    float a1 = w;
    float b1 = x;
    float c1 = y;
    float d1 = z;

    float a2 = 0;
    float b2 = vector.get_x();
    float c2 = vector.get_y();
    float d2 = vector.get_z();

    w = a1*a2 - b1*b2 - c1*c2 - d1*d2;
    x = a1*b2 + b1*a2 + c1*d2 - d1*c2;
    y = a1*c2 - b1*d2 + c1*a2 + d1*b2;
    z = a1*d2 + b1*c2 - c1*b2 + d1*a2;

    normalize();
    return;
}

void Quaternion::updateByAngularVelocity(const Vecteur3D &vector, float duration) {
    std::cout << "Error in Quaternion.cpp: idk how to do that" << std::endl;
    return;
}

Quaternion Quaternion::operator=(const Quaternion &other) {
    return Quaternion(other);
}

Quaternion operator*(const Quaternion &q1, const Quaternion &q2) {
    float a1 = q1.w;
    float b1 = q1.x;
    float c1 = q1.y;
    float d1 = q1.z;

    float a2 = q2.w;
    float b2 = q2.x;
    float c2 = q2.y;
    float d2 = q2.z;

    Quaternion result;
    result.w = a1*a2 - b1*b2 - c1*c2 - d1*d2;
    result.x = a1*b2 + b1*a2 + c1*d2 - d1*c2;
    result.y = a1*c2 - b1*d2 + c1*a2 + d1*b2;
    result.z = a1*d2 + b1*c2 - c1*b2 + d1*a2;
    result.normalize();

    return result;
}

std::ostream &operator<<(std::ostream &out, const Quaternion &quaternion) {
    return out << "(" << quaternion.w << ", " << quaternion.x << ", " << quaternion.y << ", " << quaternion.z << ")";
}
