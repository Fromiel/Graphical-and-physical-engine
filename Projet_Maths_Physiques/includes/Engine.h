#ifndef ENGINE_H
#define ENGINE_H

#include "CoreECS/Coordinator.h"
#include "Engines/Engines.h"
#include "Systems/InputsManager.h"
#include "Systems/Time.h"


/// <summary>
/// Interface utilisée par un utilisateur du moteur de jeu 
/// </summary>
class Engine
{
	private:
		static Engine* instance_;

		LogicEngine *logicEngine_; //Moteur logique
		PhysicalEngine *physicalEngine_; //Moteur physique
		GraphicEngine *graphicEngine_; //Moteur graphique

		InputsManager inputManager_;
		Time time_;

		/// <summary>
		/// Constructeur du moteur pour initialiser tous les moteurs du jeu (graphique, physique et logique)
		/// </summary>
		Engine();

	public:

		static Engine* getInstance();

		/// <summary>
		/// Methode pour lancer la boucle de jeu
		/// </summary>
		void loop();

		/// <summary>
		/// Getter du moteur physique
		/// </summary>
		/// <returns></returns>
		PhysicalEngine* getPhysicalEngine() { return physicalEngine_; }

};

#endif