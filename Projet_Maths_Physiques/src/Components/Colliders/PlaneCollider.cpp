#include "Components/Colliders/PlaneCollider.h"

PlaneCollider::PlaneCollider(Entity entity, float offs, Vecteur3D n, Vecteur3D position, Vecteur3D orientation, Rigidbody* rigidbody) : Collider(entity, position, orientation, rigidbody), offset(offs), normal(n)
{
	type_ = PlanC;
}