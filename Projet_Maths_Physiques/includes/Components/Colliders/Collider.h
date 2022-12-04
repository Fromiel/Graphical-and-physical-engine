#ifndef COLLIDER_H
#define COLLIDER_H

#include "Components/Rigidbody.h"
#include "CollisionData.h"

/// <summary>
/// Composant de base représentant un collider pour détecter les collisions entre deux objets
/// </summary>
class Collider
{
	private:
		Rigidbody *rigidbody_;
		Matrix34 offset_;

	public:
		Collider(Vecteur3D position = Vecteur3D(), Vecteur3D scale = Vecteur3D(1.0f, 1.0f, 1.0f), Vecteur3D orientation = Vecteur3D(), Rigidbody* rigidbody = NULL);

		void onCollision(const CollisionData& data) const;

};

#endif