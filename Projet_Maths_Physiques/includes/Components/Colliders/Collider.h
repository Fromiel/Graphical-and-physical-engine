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
/// Composant de base représentant un collider pour détecter les collisions entre deux objets
/// </summary>
class Collider
{
	private:
		Entity entity_;
		Rigidbody *rigidbody_;
		Matrix34 offset_;
		typeColliderEnum type_;

	public:

		Collider() {}

		Collider(Entity entity, Vecteur3D position = Vecteur3D(), Vecteur3D scale = Vecteur3D(1.0f, 1.0f, 1.0f), Vecteur3D orientation = Vecteur3D(), Rigidbody* rigidbody = NULL);

		void onCollision(const CollisionData& data) const;

		Rigidbody* getRigidbody() { return rigidbody_; }

		Entity getEntity() const { return entity_; }

		Matrix34 getOffset() const { return offset_; }

		Vecteur3D getPosition() const;

		typeColliderEnum getType() const { return type_; }

};

#endif