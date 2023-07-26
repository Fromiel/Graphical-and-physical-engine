#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "CoreECS/ECS.h"
#include <queue>
#include <array>
#include <assert.h> 

/// <summary>
/// Cette classe permet de distribuer les ids des entités en gardant en mémoire les ids utilisés et ceux qui ne le sont pas
/// </summary>
class EntityManager
{

	private:
		// File d'Id d'entités non utilisés
		std::queue<Entity> availableEntities_;

		// Tableau de signatures où l'indice correspond à un id d'une entité
		std::array<Signature, MAX_ENTITIES> signatures_;

		// Nombre d'entités : permet de limiter le nombre d'entités présents dans le jeu
		int livingEntityCount_;

	public:
		/// <summary>
		/// Constructeur de EntityManager
		/// </summary>
		EntityManager();

		/// <summary>
		/// Permet de créer une entité en lui assignant son id
		/// </summary>
		/// <returns></returns>
		Entity createEntity();

		/// <summary>
		/// Permet de détruire l'entité mise en argument
		/// </summary>
		/// <param name="entity">L'entité à détruire</param>
		void destroyEntity(Entity entity);

		/// <summary>
		/// Permet de set la signature de l'entité passée en argument par la signature passée en argument
		/// </summary>
		/// <param name="entity"></param>
		/// <param name="signature"></param>
		void setSignature(Entity entity, Signature signature);

		/// <summary>
		/// Permet de get la signature de l'entité passée en argument
		/// </summary>
		/// <param name="entity"></param>
		/// <returns></returns>
		Signature getSignature(Entity entity);

};

#endif