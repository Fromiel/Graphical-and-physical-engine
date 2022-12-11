#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "CoreECS/System.h"
#include "Components/Colliders.h"
#include "Components/Colliders/CollisionData.h"


/// <summary>
/// Système gérant les collisions (todo)
/// </summary>
class CollisionsSystem : public System
{
	private:
		int generateContactsSphereSphere(const SphereCollider& Sphere1, const SphereCollider& Sphere2, CollisionData* data);
		int generateContactsSpherePlane(const SphereCollider& Sphere, const PlaneCollider& Plan, CollisionData* data);
		int generateContactsBoxPlane(const BoxCollider& Box, const PlaneCollider& Plan, CollisionData* data);
		int generateContactsBoxSphere(const BoxCollider& Box, const SphereCollider& Sphere, CollisionData* data);
		//int generateContactsBoxBox(const BoxCollider& Box1, const BoxCollider& Box2, CollisionData* data);

	public:

		/// <summary>
		/// Methode gérant les collisions dans la boucle de jeu
		/// </summary>
		/// <param name="dt"></param>
		void update(float dt);

		/// <summary>
		/// Prend deux colliders et retourne 0, 1 ou plusieurs contacts
		/// </summary>
		/// <param name="firstCollider"></param>
		/// <param name="secondCollider"></param>
		int generateContacts(const Collider& firstCollider, const Collider& secondCollider, CollisionData *data);

};

#endif
