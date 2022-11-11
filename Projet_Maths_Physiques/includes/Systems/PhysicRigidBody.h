#ifndef PHYSICRIGIDBODY_H
#define PHYSICRIGIDBODY_H

#include "CoreECS/Coordinator.h"

/// <summary>
/// Système gérant la physique des rigidBody
/// </summary>
class PhysicRigidBody : public System
{
	private:

	public:

		/// <summary>
		/// Methode mettant a jour la position, vitesse et acceleration des rigidbody en fonctino des forces qui sont appliquees
		/// </summary>
		/// <param name="dt"></param>
		void update(float dt);
};

#endif