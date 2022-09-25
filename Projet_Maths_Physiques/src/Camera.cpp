#include "Camera.h"


Camera::Camera(float near, float far, const Vecteur3D& position, float fov, float ratio) : ratio_(ratio)
{
    if (near < 0)
        throw "near négatif";
    if (far < near)
        throw "far plus petit que near";
    if (fov < 0)
        throw "fov négatif";
    near_ = near;
    far_ = far;
    position_ = position;
    fov_ = 2 * ((float) M_PI) * fov / 360; //on passe de degrés en radians
    viewMatrix_ = Matrix4D::translation(Vecteur3D() - position);
}


void Camera::setPosition(const Vecteur3D &position)
{
    viewMatrix_ = viewMatrix_ * Matrix4D::translation(Vecteur3D() - position) * Matrix4D::translation(Vecteur3D(position_));
    position_ = position;
}


void Camera::setPosition(float x, float y, float z)
{
    setPosition(Vecteur3D(x, y, z));
}


void Camera::move(const Vecteur3D &vect)
{
    //todo
}


void Camera::rotate(float angle, const Vecteur3D &pivot)
{
    //todo
}

void Camera::lookAt(const Vecteur3D &eye, const Vecteur3D &center, const Vecteur3D &up)
{
    //todo
}



