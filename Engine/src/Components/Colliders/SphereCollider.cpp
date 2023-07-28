#include "Components/Colliders/SphereCollider.h"

SphereCollider::SphereCollider(Entity entity, float r, Vector3D position, Vector3D orientation, Rigidbody* rigidbody) : Collider(entity, position, orientation, rigidbody), radius(r)
{
	type_ = SphereC;
}