#ifndef LOGIC_H
#define LOGIC_H

#include "CoreECS/System.h"

/// <summary>
/// Syst�me g�rant les scripts de la sc�ne
/// </summary>
class Logic : public System
{
	private:
		
	public:
		/// <summary>
		/// M�thode � appeler avant la boucle de jeu pour appeler les m�thodes start de tous les scripts (LogicBehaviour) de la sc�ne
		/// </summary>
		void start();

		/// <summary>
		/// M�thode appel� � chaque frame qui va appeler toutes les m�thodes update des scripts (LogicBehaviour) de la sc�ne
		/// </summary>
		/// <param name="dt"></param>
		void update(float dt);

};

#endif