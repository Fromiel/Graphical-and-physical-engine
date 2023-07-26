#ifndef PHYSICRIGIDBODY_H
#define PHYSICRIGIDBODY_H

#include "CoreECS/Coordinator.h"
#include "Forces/ForceRegistry.h"

/// <summary>
/// Système gérant la physique des rigidBody
/// </summary>
class PhysicRigidBody : public System
{
	private:
		ForceRegistry _registry;
	public:

		/// <summary>
		/// Methode mettant a jour la position, vitesse et acceleration des rigidbody en fonctino des forces qui sont appliquees
		/// </summary>
		/// <param name="dt"></param>
		void update(float dt);

		/// <summary>
		/// Ajoute une force au forceRegistry
		/// </summary>
		/// <returns></returns>
		void addForce(Rigidbody* rb, ForceGenerator* fg) { _registry.add(rb, fg); }
};

#endif