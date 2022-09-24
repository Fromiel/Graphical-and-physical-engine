#include "Object3D.h"

void Object3D::setPosition(Vecteur3D position)
{
	modelMatrix_ = modelMatrix_ * Matrix4D::translation(position) * Matrix4D::translation(Vecteur3D( Vecteur3D() - position_));
	position_ = position;
}

void Object3D::setScaling(Vecteur3D scale)
{
	modelMatrix_ = modelMatrix_ * Matrix4D::scaling(scale) * (Matrix4D::scaling(Vecteur3D(scaling_)).invert());
	scaling_ = scale;
}

void Object3D::move(Vecteur3D vect)
{
	//todo
}

void Object3D::rotate(float angle, Vecteur3D pivot)
{
	//todo
}

