#ifndef	LOGICENGINE_H
#define LOGICENGINE_H

#include "CoreECS/Coordinator.h"
#include "Systems/Logic.h"

/// <summary>
/// Class gerant la partie logique du jeu (notamment permettre de rajouter facilement du code dans la boucle de jeu pour creer un jeu)
/// </summary>
class LogicEngine
{
	private:
		Coordinator* coordinator_; //Pointeur vers coordinator pour gerer l'architecture ECS

		std::shared_ptr<Logic> logicSystem_; //Pointeur vers le system Logic

	public:
		/// <summary>
		/// Constructeur qui va initialiser le moteur logique
		/// </summary>
		LogicEngine();

		/// <summary>
		/// Methode appelee pour mettre à jour le moteur logique en fonction du temps qui s'est écoulé avec la dernière frame
		/// </summary>
		/// <param name="dt">Temps qui s'est écoulé avec la dernière frame</param>
		void update(float dt);

		/// <summary>
		/// Methode appelee par le moteur logique avant la premiere frame
		/// </summary>
		void start();
};

#endif