#ifndef	GRAPHICENGINE_H
#define GRAPHICENGINE_H

#include "CoreECS/Coordinator.h"
#include "Systems/Render.h"

/// <summary>
/// Classe gérant l'affichage graphique du jeu
/// </summary>
class GraphicEngine
{
	private:
		Coordinator* coordinator_; //Pointeur vers Coordinator pour gerer l'architecture ECS

		std::shared_ptr<Render> renderSystem_; //Pointeur vers le systeme Render

	public:
		/// <summary>
		/// Constructeur qui va initialiser le moteur graphique
		/// </summary>
		GraphicEngine();


		/// <summary>
		/// Methode appelee pour mettre à jour le moteur graphique en fonction du temps qui s'est écoulé avec la dernière frame
		/// </summary>
		/// <param name="dt">Temps qui s'est écoulé avec la dernière frame</param>
		void update(float dt);

		/// <summary>
		/// Getter de renderSystem (utilise pour obtenir le pointeur de la fenetre)
		/// </summary>
		/// <returns></returns>
		std::shared_ptr<Render> getRenderSystem() const { return renderSystem_; }
};

#endif