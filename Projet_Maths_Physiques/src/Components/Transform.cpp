#include "Components/Transform.h"


void Transform::computeModelMatrix()
{
	//std::cout << "On compute la nouvelle model matrix" << std::endl;

	Matrix34 translationOrientation;

	translationOrientation.setOrientationAndPosition(orientation_, position_);
	
	//std::cout << "scale = " << Matrix34::scaling(scale_) << " (scale = " << scale_ << ")" << std::endl;

	modelMatrix_ = translationOrientation * Matrix34::scaling(scale_);

	//std::cout << "Nouvelle matrice = " << modelMatrix_ << std::endl;
}


Transform::Transform(Vecteur3D position, Vecteur3D scaling, Quaternion orientation) : scale_(scaling), position_(position), orientation_(orientation)
{
	computeModelMatrix();
}

Transform::Transform(Vecteur3D position, Vecteur3D scaling, Vecteur3D orientation) : position_(position), scale_(scaling), orientation_(orientation)
{
	computeModelMatrix();
}

void Transform::setPosition(const Vecteur3D& position)
{
	position_ = position;
	computeModelMatrix();
}

void Transform::setScaling(const Vecteur3D& scale)
{
	scale_ = scale;
	computeModelMatrix();
}

void Transform::setOrientation(const Quaternion& orientation)
{
	orientation_ = orientation;
	computeModelMatrix();
}

void Transform::move(const Vecteur3D& vect)
{
	Matrix34 orientation;
	orientation.setOrientationAndPosition(orientation_, Vecteur3D());

	Vecteur3D v = orientation.transformDirection(vect);

	position_ = position_ + v;

	computeModelMatrix();
}

void Transform::rotate(float angle, const Vecteur3D& pivot)
{
	//orientation_.rotateByVector(angle * pivot);
	Quaternion r(angle * pivot);
	orientation_ = orientation_ * r;


	computeModelMatrix();
}