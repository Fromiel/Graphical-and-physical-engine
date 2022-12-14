#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "CoreECS/System.h"
#include "Components/Colliders.h"
#include "Components/Colliders/CollisionData.h"


/// <summary>
/// Syst�me g�rant les collisions (todo)
/// </summary>
class CollisionsSystem : public System
{
	private:
		int generateContactsSphereSphere(const SphereCollider* Sphere1, const SphereCollider* Sphere2, std::vector<CollisionData>* data);
		int generateContactsSpherePlane(const SphereCollider* Sphere, const PlaneCollider* Plan, std::vector<CollisionData>* data);
		int generateContactsBoxPlane(const BoxCollider* Box, const PlaneCollider* Plan, std::vector<CollisionData>* data);
		int generateContactsBoxSphere(const BoxCollider* Box, const SphereCollider* Sphere, std::vector<CollisionData>* data);
		//int generateContactsBoxBox(const BoxCollider& Box1, const BoxCollider& Box2, std::vector<CollisionData>* data);

	public:

		/// <summary>
		/// Methode g�rant les collisions dans la boucle de jeu
		/// </summary>
		/// <param name="dt"></param>
		void update(float dt);

		/// <summary>
		/// Prend deux colliders et retourne 0, 1 ou plusieurs contacts
		/// </summary>
		/// <param name="firstCollider"></param>
		/// <param name="secondCollider"></param>
		int generateContacts(Collider* firstCollider, Collider* secondCollider, std::vector<CollisionData> *data);

};

#endif
