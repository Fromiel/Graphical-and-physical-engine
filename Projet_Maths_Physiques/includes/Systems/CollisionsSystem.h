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
		void generateContacts(const Collider& firstCollider, const Collider& secondCollider, CollisionData *data);

};

#endif
