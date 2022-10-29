#ifndef LOGIC_H
#define LOGIC_H

#include "CoreECS/System.h"

/// <summary>
/// Système gérant les scripts de la scène
/// </summary>
class Logic : public System
{
	private:
		
	public:
		/// <summary>
		/// Méthode à appeler avant la boucle de jeu pour appeler les méthodes start de tous les scripts (LogicBehaviour) de la scène
		/// </summary>
		void start();

		/// <summary>
		/// Méthode appelé à chaque frame qui va appeler toutes les méthodes update des scripts (LogicBehaviour) de la scène
		/// </summary>
		/// <param name="dt"></param>
		void update(float dt);

};

#endif