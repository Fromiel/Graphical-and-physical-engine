#include "Components/Transform.h"

Transform::Transform(Vecteur3D position, Vecteur3D scaling) : rotation_(), scale_(scaling), position_(position)
{
	modelMatrix_ = Matrix4D::translation(position_) * Matrix4D::scaling(scale_);
}

void Transform::setPosition(const Vecteur3D& position)
{
	modelMatrix_ = modelMatrix_ * Matrix4D::translation(position) * Matrix4D::translation(Vecteur3D(Vecteur3D() - position_));
	position_ = position;
}

void Transform::setScaling(const Vecteur3D& scale)
{
	modelMatrix_ = modelMatrix_ * Matrix4D::scaling(scale) * (Matrix4D::scaling(Vecteur3D(scale_)).invert());
	scale_ = scale;
}

void Transform::move(const Vecteur3D& vect)
{
	//todo
}

void Transform::rotate(float angle, const Vecteur3D& pivot)
{
	//todo
}