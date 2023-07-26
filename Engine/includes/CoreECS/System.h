#ifndef SYSTEM_H
#define SYSTEM_H

#include "CoreECS/Ecs.h"
#include <set>

/// <summary>
/// Classe représentant un système
/// </summary>
class System
{
	protected:
		//Ensemble d'entités
		std::set<Entity> entities_;
	public:
		/// <summary>
		/// Retourne l'ensemble d'entités
		/// </summary>
		/// <returns></returns>
		std::set<Entity> getEntities() { return entities_; }

		/// <summary>
		/// Méthode virtuelle pour ajouter une entité
		/// </summary>
		/// <param name="entity"></param>
		virtual void insertEntity(Entity entity) { entities_.insert(entity); }

		/// <summary>
		/// Méthode virtuelle pour supprimer une entité
		/// </summary>
		/// <param name="entity"></param>
		virtual void eraseEntity(Entity entity){ entities_.erase(entity); }
};


#endif SYSTEM_H
