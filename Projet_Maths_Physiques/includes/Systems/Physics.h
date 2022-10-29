#ifndef PHYSICS_H
#define PHYSICS_H

#include "CoreECS/Coordinator.h"

/// <summary>
/// Syst�me g�rant la physique (pour l'instant que gravit�)
/// </summary>
class Physics : public System
{
	private:

	public:
		/// <summary>
		/// Met � jour la physique de tous 
		/// </summary>
		/// <param name="dt"></param>
		void update(float dt);

};


#endif