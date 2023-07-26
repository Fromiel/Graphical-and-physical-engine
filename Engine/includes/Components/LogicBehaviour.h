#ifndef LOGICBEHAVIOUR_H
#define LOGICBEHAVIOUR_H

#include "CoreECS/Coordinator.h"
#include <functional>

/// <summary>
/// Classe
/// </summary>
class LogicBehaviour
{
	protected:
		Entity entity_;
		std::function<void()> start_;
		std::function<void(float)> update_;

	public:

		/// <summary>
		/// Constructeur par d�faut
		/// </summary>
		LogicBehaviour() {}

		/// <summary>
		/// Constructeur pr�cisant l'entit� � laquelle appartient ce component
		/// </summary>
		/// <param name="entity"></param>
		LogicBehaviour(Entity entity);

		void start()
		{
			start_();
		}

		void update(float dt)
		{
			update_(dt);
		}

};

#endif