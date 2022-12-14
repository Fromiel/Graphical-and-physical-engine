#ifndef COLLIDER_H
#define COLLIDER_H

#include "Components/Rigidbody.h"
#include "CollisionData.h"


enum typeColliderEnum
{
	PlanC,
	SphereC,
	BoxC
};
/// <summary>
/// Composant de base repr�sentant un collider pour d�tecter les collisions entre deux objets
/// </summary>
class Collider
{
	protected:
		Entity entity_;
		Rigidbody *rigidbody_;
		Matrix34 offset_;
		typeColliderEnum type_;

	public:

		Collider() {}

		Collider(Entity entity, Vecteur3D position = Vecteur3D(), Vecteur3D orientation = Vecteur3D(), Rigidbody* rigidbody = NULL);

		void onCollision(const CollisionData& data) const;

		Rigidbody* getRigidbody() { return rigidbody_; }

		Entity getEntity() const { return entity_; }

		Matrix34 getOffset() const { return offset_; }

		Vecteur3D getPosition() const;

		typeColliderEnum getType() const { return type_; }

};

#endif