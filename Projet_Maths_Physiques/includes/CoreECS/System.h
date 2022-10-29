#ifndef SYSTEM_H
#define SYSTEM_H

#include "CoreECS/Ecs.h"
#include <set>

/// <summary>
/// Classe repr�sentant un syst�me
/// </summary>
class System
{
	protected:
		//Ensemble d'entit�s
		std::set<Entity> entities_;
	public:
		/// <summary>
		/// Retourne l'ensemble d'entit�s
		/// </summary>
		/// <returns></returns>
		std::set<Entity> getEntities() { return entities_; }

		/// <summary>
		/// M�thode virtuelle pour ajouter une entit�
		/// </summary>
		/// <param name="entity"></param>
		virtual void insertEntity(Entity entity) { entities_.insert(entity); }

		/// <summary>
		/// M�thode virtuelle pour supprimer une entit�
		/// </summary>
		/// <param name="entity"></param>
		virtual void eraseEntity(Entity entity){ entities_.erase(entity); }
};


#endif SYSTEM_H
