#include "Components/Colliders/PlaneCollider.h"

PlaneCollider::PlaneCollider(Entity entity, float halfSX, float halfSZ, Vecteur3D position, Vecteur3D orientation, Rigidbody* rigidbody) : Collider(entity, position, orientation, rigidbody), halfSizeX(halfSX), halfSizeZ(halfSZ)
{
	type_ = PlanC;
}


float PlaneCollider::getMaxSize() const 
{
	if (halfSizeX > halfSizeZ) return halfSizeX;
	return halfSizeZ;
}