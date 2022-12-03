#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "CoreECS/System.h"


/// <summary>
/// Système gérant les collisions (todo)
/// </summary>
class Collisions : public System
{
	private:


	public:

		/// <summary>
		/// Methode gérant les collisions dans la boucle de jeu
		/// </summary>
		/// <param name="dt"></param>
		void update(float dt);

};

#endif
