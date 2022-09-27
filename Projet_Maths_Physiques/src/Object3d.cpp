#include "Object3D.h"

Object3D::Object3D(Vecteur3D position, Vecteur3D scaling) : position_(position), scaling_(scaling)
{
	modelMatrix_ = Matrix4D::translation(position_) * Matrix4D::scaling(scaling_);
}

void Object3D::setPosition(const Vecteur3D &position)
{
	modelMatrix_ = modelMatrix_ * Matrix4D::translation(position) * Matrix4D::translation(Vecteur3D( Vecteur3D() - position_));
	position_ = position;
}

void Object3D::setScaling(const Vecteur3D& scale)
{
	modelMatrix_ = modelMatrix_ * Matrix4D::scaling(scale) * (Matrix4D::scaling(Vecteur3D(scaling_)).invert());
	scaling_ = scale;
}

void Object3D::move(const Vecteur3D &vect)
{
	//todo
}

void Object3D::rotate(float angle, const Vecteur3D &pivot)
{
	//todo
}


