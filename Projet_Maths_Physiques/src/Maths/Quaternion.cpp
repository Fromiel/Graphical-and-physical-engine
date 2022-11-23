#include "Maths/Quaternion.h"

Quaternion::Quaternion(float w, float x, float y, float z, bool shouldNormalize) : w(w), x(x), y(y), z(z) {
    if (w == x && x == y && y == z && z == 0) w = 1; 
    if (shouldNormalize) normalize();
    return;
}

Quaternion::Quaternion(const Vecteur3D &orientation)
{
    double cr = cos(orientation.get_x() * 0.5);
    double sr = sin(orientation.get_x() * 0.5);
    double cp = cos(orientation.get_y() * 0.5);
    double sp = sin(orientation.get_y() * 0.5);
    double cy = cos(orientation.get_z() * 0.5);
    double sy = sin(orientation.get_z() * 0.5);

    w = cr * cp * cy + sr * sp * sy;
    x = sr * cp * cy - cr * sp * sy;
    y = cr * sp * cy + sr * cp * sy;
    z = cr * cp * sy - sr * sp * cy;
}

Quaternion::Quaternion(const Quaternion &other) {
    this->w = other.w;
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    return;
}

Quaternion::~Quaternion() {
    return;
}

void Quaternion::normalize() {
    float magnitude = static_cast<float>(sqrt(pow(w, 2) + pow(x, 2) + pow(y, 2) + pow(z, 2)));
    if (magnitude != 0) {
        w /= magnitude;
        x /= magnitude;
        y /= magnitude;
        z /= magnitude;
    }
    else {
        w = 0;
        x = 0;
        y = 0;
        z = 0;
    }
    
    return;
}

void Quaternion::rotateByVector(const Vecteur3D &vector) {
    Quaternion rotation = Quaternion(0, vector.get_x(), vector.get_y(), vector.get_z(), false);
    Quaternion result = (*this) * rotation;
    w = result.w;
    x = result.x;
    y = result.y;
    z = result.z;
    normalize();
    return;
}

void Quaternion::updateByAngularVelocity(const Vecteur3D &vector, float duration) {
    Quaternion rotation = Quaternion(0, vector.get_x() * duration, vector.get_y() * duration, vector.get_z() * duration, false);
    Quaternion result = rotation * (*this);
    w += result.w * 0.5f;
    x += result.x * 0.5f;
    y += result.y * 0.5f;
    z += result.z * 0.5f;

    normalize();
    return;
}

std::vector<float> Quaternion::getContentAsStdVector() const {
    return std::vector<float>({w, x, y, z});
}

void Quaternion::operator=(const Quaternion &other) {
    w = other.w;
    x = other.x;
    y = other.y;
    z = other.z;
    return;
}

void Quaternion::operator*=(const Quaternion &other) {
    Quaternion result = (*this) * other;
    w = result.w;
    x = result.x;
    y = result.y;
    z = result.z;
    return;
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
