#ifndef SYSTEMMANAGER
#define SYSTEMMANAGER

#include "CoreECS/System.h"
#include "CoreECS/ECS.h"

#include <unordered_map>
#include <memory>
#include <assert.h>

/// <summary>
/// Classe gardant en mémoire les sytèmes créés ainsi que leur signature
/// </summary>
class SystemManager
{
	private:
		// Map d'un string d'un type System vers une signature
		std::unordered_map<const char*, Signature> signatures_;

		// Map d'un string d'un type System le pointeur d'un System
		std::unordered_map<const char*, std::shared_ptr<System>> systems_;

	public:

		/// <summary>
		/// Enregistre un System et le retourne
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template<typename T>
		std::shared_ptr<T> registerSystem()
		{
			const char* typeName = typeid(T).name();

			assert(systems_.find(typeName) == systems_.end() && "Registering system more than once.");

			auto system = std::make_shared<T>();
			systems_.insert({ typeName, system });
			return system;
		}

		/// <summary>
		/// Set la signature pour le système T
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="signature"></param>
		template<typename T>
		void setSignature(Signature signature)
		{
			const char* typeName = typeid(T).name();

			assert(systems_.find(typeName) != systems_.end() && "System used before registered.");

			signatures_.insert({ typeName, signature });
		}
		
		/// <summary>
		/// Supprime une entité détruite de tous les ensembles des systèmes
		/// </summary>
		/// <param name="entity"></param>
		void entityDestroyed(Entity entity);

		/// <summary>
		/// Notifie chaque sytème que la signature d'une entité a changé et ajouter ou supprimer l'entité des systèmes en fonction de la nouvelle signature
		/// </summary>
		/// <param name="entity"></param>
		/// <param name="entitySignature"></param>
		void entitySignatureChanged(Entity entity, Signature entitySignature);

};



#endif