#include "Components/Colliders/BoxCollider.h"


BoxCollider::BoxCollider(Entity entity, Vector3D halfS, Vector3D position, Vector3D orientation, Rigidbody* rigidbody) : Collider(entity, position, orientation, rigidbody), halfsize(halfS)
{
	type_ = BoxC;
}

float BoxCollider::getMaxSize() const
{
	return halfsize.maxValue();
}