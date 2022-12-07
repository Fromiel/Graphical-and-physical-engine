#include "Systems/CollisionsSystem.h"
#include "Bounding/BVHNode.h"
#include "Bounding/BoundingSphere.h"
#include "Components/Transform.h"

void CollisionsSystem::update(float dt)
{
	Coordinator* coordinator = Coordinator::getInstance();

	//Colliders
	std::vector<Collider> colliders;
	
	// 1) Construire BVH
	BVHNode<BoundingSphere> bvh;
	for (auto gameObject : entities_)
	{
		auto collider = coordinator->getComponent<Collider>(gameObject);
		colliders.push_back(collider);
		// Inserer ce collider dans le bvh
		Transform t = coordinator->getComponent<Transform>(gameObject);
		BoundingSphere bs(t.getPosition(), t.maxScale());
		bvh.insert(collider.getRigidbody(), bs);
	}

	// 2) Detecter les collisions possibles
	PotentialContact potentialContacts[100];

	int nbPotentialContact = bvh.getPotentialContacts(potentialContacts, 100);

	// 3) Calculer vrai collisions
	for (int i = 0; i < nbPotentialContact; i++)
	{
		//todo : generer tous les contacts pour tous les contacts potentiels
	}

	// 4) Resoudre les collisions




}