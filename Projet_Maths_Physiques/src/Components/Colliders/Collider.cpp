#include "Components/Colliders/Collider.h"
#include "Components/Transform.h"



Collider::Collider(Entity entity, Vecteur3D position, Vecteur3D scale, Vecteur3D orientation, Rigidbody* rigidbody) : rigidbody_(rigidbody)
{

}

Vecteur3D Collider::getPosition() const {
	Vecteur3D pos = Coordinator::getInstance()->getComponent<Transform>(entity_).getPosition();
	return offset_ * pos;
}