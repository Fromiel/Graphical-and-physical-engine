#include "Components/Colliders/SphereCollider.h"

SphereCollider::SphereCollider(Entity entity, float r, Vecteur3D position, Vecteur3D orientation, Rigidbody* rigidbody) : Collider(entity, position, orientation, rigidbody), radius(r)
{
	type_ = SphereC;
}