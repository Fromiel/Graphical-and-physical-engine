#include "Components/Colliders/Collider.h"
#include "Components/Transform.h"



Collider::Collider(Entity entity, Vector3D position, Vector3D orientation, Rigidbody* rigidbody) : entity_(entity), rigidbody_(rigidbody), offset_(Matrix34())
{
	offset_.setOrientationAndPosition(Quaternion(orientation), position);
}

Vector3D Collider::getPosition() const {
	Vector3D pos = Coordinator::getInstance()->getComponent<Transform>(entity_).getPosition();
	return offset_ * pos;
}

Matrix34 Collider::getWorldPositionOrientation() const
{
	return Coordinator::getInstance()->getComponent<Transform>(entity_).getWorldMatrix() * offset_;
}