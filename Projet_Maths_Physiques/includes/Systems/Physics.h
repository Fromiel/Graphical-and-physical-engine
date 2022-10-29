#ifndef PHYSICS_H
#define PHYSICS_H

#include "CoreECS/Coordinator.h"

/// <summary>
/// Système gérant la physique (pour l'instant que gravité)
/// </summary>
class Physics : public System
{
	private:

	public:
		/// <summary>
		/// Met à jour la physique de tous 
		/// </summary>
		/// <param name="dt"></param>
		void update(float dt);

};


#endif