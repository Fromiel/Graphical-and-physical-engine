#ifndef COORDINATOR_H
#define COORDINATOR_H

#include "SystemManager.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "Components.h"

/// <summary>
/// Classe servant d'interface pour manipuler les entit�s, components et syst�mes
/// </summary>
class Coordinator
{
	private:
		static Coordinator* instance_;

		std::unique_ptr<ComponentManager> componentManager_;
		std::unique_ptr<EntityManager> entityManager_;
		std::unique_ptr<SystemManager> systemManager_;

		/// <summary>
		/// Constructeur cr�ant un pointeur vers chaque managers
		/// </summary>
		Coordinator();

		Coordinator& operator=(Coordinator&&) = default;

	public:

		static Coordinator *getInstance();

		static void resetInstance() { 
			delete instance_;
			instance_ = NULL;
		}

		// -----------Entity methods--------------

		/// <summary>
		/// Methode pour cr�er une entit�
		/// </summary>
		/// <returns>L'entit� cr��e</returns>
		Entity createEntity();

		/// <summary>
		/// D�truit l'entit� pass�e en argument
		/// </summary>
		/// <param name="entity"></param>
		void destroyEntity(Entity entity);


		// ----------Component methods----------------------

		/// <summary>
		/// Permet d'enregistrer un type T de Component
		/// </summary>
		/// <typeparam name="T"></typeparam>
		template<typename T>
		void registerComponent() { componentManager_->registerComponent<T>(); }

		/// <summary>
		/// Ajoute un component T pour une entit� donn�e � son ComponentArray associ�
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="entity"></param>
		/// <param name="component"></param>
		template<typename T>
		void addComponent(Entity entity, T component)
		{
			componentManager_->addComponent<T>(entity, component);

			auto signature = entityManager_->getSignature(entity);
			signature.set(componentManager_->getComponentType<T>(), true);
			entityManager_->setSignature(entity, signature);

			systemManager_->entitySignatureChanged(entity, signature);
		}

		/// <summary>
		/// Enl�ve un component T pour une entit� donn�e � son ComponentArray associ�
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="entity"></param>
		template<typename T>
		void removeComponent(Entity entity)
		{
			componentManager_->removeComponent<T>(entity);

			auto signature = entityManager_->getSignature(entity);
			signature.set(componentManager_->getComponentType<T>(), false);
			entityManager_->setSignature(entity, signature);

			systemManager_->entitySignatureChanged(entity, signature);
		}


		/// <summary>
		/// Retourne une r�f�rence vers un component T de l'entit� pass�e en argument
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="entity"></param>
		/// <returns></returns>
		template<typename T>
		T& getComponent(Entity entity) {return componentManager_->getComponent<T>(entity);}

		template<typename T>
		T* getComponentPtr(Entity entity) { return componentManager_->getComponentPtr<T>(entity); }


		/// <summary>
		/// Permet de savoir si une entit� poss�de un component de type T
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="entity"></param>
		/// <returns>True si l'entit� poss�de ce component, false sinon</returns>
		template<typename T>
		bool hasComponent(Entity entity) { return componentManager_->hasComponent<T>(entity); }


		/// <summary>
		/// Retourne le type du component T (utilis� pour cr�er les signatures)
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template<typename T>
		ComponentType getComponentType() { return componentManager_->getComponentType<T>(); }


		// ----------System methods--------------

		/// <summary>
		/// Enregistre un System et le retourne
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template<typename T>
		std::shared_ptr<T> registerSystem() { return systemManager_->registerSystem<T>(); }

		/// <summary>
		/// Set la signature pour le syst�me T
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="signature"></param>
		template<typename T>
		void setSystemSignature(Signature signature) { systemManager_->setSignature<T>(signature); }

};


#endif