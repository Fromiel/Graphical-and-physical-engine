#include "Components/Camera.h"
#include "CoreECS/Coordinator.h"

Camera::Camera(Entity entity, float near, float far, float fov, float ratio) : cameraEntity_(entity), ratio_(ratio)
{
    Coordinator* coordinator = Coordinator::getInstance();
    if (near < 0)
        throw "near négatif";
    if (far < near)
        throw "far plus petit que near";
    if (fov < 0)
        throw "fov négatif";
    if (!coordinator->hasComponent<Transform>(cameraEntity_))
        throw "camera a besoin d'un transform";

    Transform transform = coordinator->getComponent<Transform>(cameraEntity_);
    

    near_ = near;
    far_ = far;
    fov_ = 2 * ((float) M_PI) * fov / 360; //on passe de degrés en radians
    viewMatrix_ = Matrix4D::translation(Vecteur3D() - transform.getPosition());
}


Camera::Camera(Transform transform, float near, float far, float fov, float ratio): ratio_(ratio)
{
    Coordinator* coordinator = Coordinator::getInstance();
    if (near < 0)
        throw "near négatif";
    if (far < near)
        throw "far plus petit que near";
    if (fov < 0)
        throw "fov négatif";
    near_ = near;
    far_ = far;
    fov_ = 2 * ((float)M_PI) * fov / 360; //on passe de degrés en radians
    viewMatrix_ = Matrix4D::translation(Vecteur3D() - transform.getPosition());
}

Matrix3D Camera::getNormalMatrix(Matrix4D modelMatrix)
{
    Matrix4D modelView = viewMatrix_ * modelMatrix;
    Matrix3D upperLeftModelView;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            upperLeftModelView(i, j) = modelView(i, j);
        }
    }
    Matrix3D normalMatrix = upperLeftModelView.invert();

    return normalMatrix;
}

Matrix4D Camera::projectionMatrix()
{
    Matrix4D projMatrix;
    float tan_half_angle;
    tan_half_angle = tan(fov_ / 2);
    projMatrix(0, 0) = 1 / (ratio_ * tan_half_angle);
    projMatrix(1, 1) = 1 / (tan_half_angle);
    projMatrix(2, 2) = -(far_ + near_) / (far_ - near_);
    projMatrix(3, 2) = -1;
    projMatrix(2, 3) = -(2 * far_ * near_) / (far_ - near_);
    return projMatrix;
}


void Camera::movePosition(Vecteur3D move)
{
    Coordinator* coordinator = Coordinator::getInstance();
    Transform& transform =  coordinator->getComponent<Transform>(cameraEntity_);
    Vecteur3D newPos = transform.getPosition() + move;
    transform.setPosition(newPos);
    viewMatrix_ = Matrix4D::translation(Vecteur3D() - transform.getPosition());
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



