#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "CoreECS/ECS.h"
#include <queue>
#include <array>
#include <assert.h> 

/// <summary>
/// Cette classe permet de distribuer les ids des entit�s en gardant en m�moire les ids utilis�s et ceux qui ne le sont pas
/// </summary>
class EntityManager
{

	private:
		// File d'Id d'entit�s non utilis�s
		std::queue<Entity> availableEntities_;

		// Tableau de signatures o� l'indice correspond � un id d'une entit�
		std::array<Signature, MAX_ENTITIES> signatures_;

		// Nombre d'entit�s : permet de limiter le nombre d'entit�s pr�sents dans le jeu
		int livingEntityCount_;

	public:
		/// <summary>
		/// Constructeur de EntityManager
		/// </summary>
		EntityManager();

		/// <summary>
		/// Permet de cr�er une entit� en lui assignant son id
		/// </summary>
		/// <returns></returns>
		Entity createEntity();

		/// <summary>
		/// Permet de d�truire l'entit� mise en argument
		/// </summary>
		/// <param name="entity">L'entit� � d�truire</param>
		void destroyEntity(Entity entity);

		/// <summary>
		/// Permet de set la signature de l'entit� pass�e en argument par la signature pass�e en argument
		/// </summary>
		/// <param name="entity"></param>
		/// <param name="signature"></param>
		void setSignature(Entity entity, Signature signature);

		/// <summary>
		/// Permet de get la signature de l'entit� pass�e en argument
		/// </summary>
		/// <param name="entity"></param>
		/// <returns></returns>
		Signature getSignature(Entity entity);

};

#endif