#include "Components/Colliders/BoxCollider.h"


BoxCollider::BoxCollider(Entity entity, Vecteur3D halfS, Vecteur3D position, Vecteur3D orientation, Rigidbody* rigidbody) : Collider(entity, position, orientation, rigidbody), halfsize(halfS)
{
	type_ = BoxC;
}