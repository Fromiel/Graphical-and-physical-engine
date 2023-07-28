#include "Components/Camera.h"
#include "CoreECS/Coordinator.h"


void Camera::computeViewMatrix()
{
    Transform transform = Coordinator::getInstance()->getComponent<Transform>(cameraEntity_);

    Matrix34 tmp;
    tmp.setOrientationAndPosition(transform.getOrientation(), transform.getPosition());
    viewMatrix_ = tmp.invert();
}

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
    
    near_ = near;
    far_ = far;
    fov_ = 2 * ((float) M_PI) * fov / 360; //on passe de degrés en radians
    computeViewMatrix();
}


Matrix3D Camera::getNormalMatrix(Matrix34 modelMatrix)
{
    Matrix34 modelView = viewMatrix_ * modelMatrix;
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


void Camera::movePosition(Vector3D move)
{
    Coordinator* coordinator = Coordinator::getInstance();
    Transform& transform =  coordinator->getComponent<Transform>(cameraEntity_);
    Vector3D newPos = transform.getPosition() + move;
    transform.setPosition(newPos);
    computeViewMatrix();
}


void Camera::move(const Vector3D &vect)
{
    Coordinator* coordinator = Coordinator::getInstance();
    Transform& transform = coordinator->getComponent<Transform>(cameraEntity_);
    transform.move(vect);
    computeViewMatrix();
}


void Camera::rotate(float angle, const Vector3D &pivot)
{
    Coordinator* coordinator = Coordinator::getInstance();
    Transform& transform = coordinator->getComponent<Transform>(cameraEntity_);
    transform.rotate(angle, pivot);
    computeViewMatrix();
}

void Camera::lookAt(const Vector3D &eye, const Vector3D &center, const Vector3D &up)
{
    //todo
}



