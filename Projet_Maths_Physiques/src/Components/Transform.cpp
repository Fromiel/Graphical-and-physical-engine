#include "Components/Transform.h"

void Transform::computeModelMatrix()
{
	Matrix34 translationOrientation;
	translationOrientation.setOrientationAndPosition(orientation_, position_);
	modelMatrix_ = translationOrientation * Matrix34::scaling(scale_);
	modelChanged_ = false;
}


Transform::Transform(Vecteur3D position, Vecteur3D scaling, Quaternion orientation) : scale_(scaling), position_(position), orientation_(orientation), modelChanged_(true)
{
	
}

Transform::Transform(Vecteur3D position, Vecteur3D scaling, Vecteur3D orientation) : position_(position), scale_(scaling), orientation_(orientation), modelChanged_(true)
{
	
}

void Transform::setPosition(const Vecteur3D& position)
{
	position_ = position;
	modelChanged_ = true;
}

void Transform::setScaling(const Vecteur3D& scale)
{
	scale_ = scale;
	modelChanged_ = true;
}

void Transform::setOrientation(const Quaternion& orientation)
{
	orientation_ = orientation;
	modelChanged_ = true;
}

void Transform::move(const Vecteur3D& vect)
{
	Matrix34 orientation;
	orientation.setOrientationAndPosition(orientation_, Vecteur3D());

	Vecteur3D v = orientation.transformDirection(vect);

	position_ = position_ + v;

	modelChanged_ = true;
}

void Transform::rotate(float angle, const Vecteur3D& pivot)
{
	Quaternion r(angle * pivot);
	orientation_ = orientation_ * r;

	modelChanged_ = true;
}

Matrix34 Transform::getModelMatrix()
{
	if (modelChanged_)
		computeModelMatrix();

	return modelMatrix_;
}


float Transform::maxScale()
{
	float m = scale_.get_x();
	if (m < scale_.get_y())
		m = scale_.get_y();
	if (m < scale_.get_z())
		m = scale_.get_z();
	return m;
}