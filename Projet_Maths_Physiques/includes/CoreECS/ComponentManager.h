#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "ComponentArray.h"
#include <memory>

/// <summary>
/// Classe faisant le lien entre tous les diff�rents ComponentArrays lorsqu'un composant doit �tre ajout� ou supprim�
/// </summary>
class ComponentManager
{
	private:
		// Map d'un pointeur de string vers un component
		std::unordered_map<const char*, ComponentType> componentTypes_;

		// Map d'un pointeur de string vers un ComponentArray
		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays_;

		// Le type de component qui doit �tre enregistr� � l'ajout du prochain component (en commencant � 0)
		ComponentType nextComponentType_;

		// Fonction utilis�e pour obtenir le pointeur vers un ComponentArray qu'on a caster vers le type ComponentArray<T>
		template<typename T>
		std::shared_ptr<ComponentArray<T>> getComponentArray()
		{
			const char* typeName = typeid(T).name();

			assert(componentTypes_.find(typeName) != componentTypes_.end() && "Component not registered before use.");

			return std::static_pointer_cast<ComponentArray<T>>(componentArrays_[typeName]);
		}

	public:
		/// <summary>
		/// Constructeur du ComponentManager
		/// </summary>
		ComponentManager() : nextComponentType_(0) {}

		/// <summary>
		/// Permet d'enregistrer un type T de Component
		/// </summary>
		/// <typeparam name="T"></typeparam>
		template<typename T>
		void registerComponent()
		{
			const char* typeName = typeid(T).name();

			assert(componentTypes_.find(typeName) == componentTypes_.end() && "Registering component type more than once.");

			// Ajoute ce type de component � la map de components
			componentTypes_.insert({ typeName, nextComponentType_ });

			// Cr�� un pointeur de ComponentArray et l'ajoute � la map de ComponentArrays
			componentArrays_.insert({ typeName, std::make_shared<ComponentArray<T>>() });

			// Incr�ment la valeur pour que le prochain component qui sera ajout� aura un type diff�rent
			nextComponentType_++;
		}

		/// <summary>
		/// Retourne le type du component T (utilis� pour cr�er les signatures)
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template<typename T>
		ComponentType getComponentType()
		{
			const char* typeName = typeid(T).name();

			assert(componentTypes_.find(typeName) != componentTypes_.end() && "Component not registered before use.");

			// Retourne le type de ce component
			return componentTypes_[typeName];
		}

		/// <summary>
		/// Ajoute un component T pour une entit� donn�e � son ComponentArray associ�
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="entity"></param>
		/// <param name="component"></param>
		template<typename T>
		void addComponent(Entity entity, T component) { getComponentArray<T>()->insertData(entity, component); }

		/// <summary>
		/// Enl�ve un component T pour une entit� donn�e � son ComponentArray associ�
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="entity"></param>
		template<typename T>
		void removeComponent(Entity entity) { getComponentArray<T>()->removeData(entity); }

		/// <summary>
		/// Retourne une r�f�rence vers un component T de l'entit� pass�e en argument
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="entity"></param>
		/// <returns></returns>
		template<typename T>
		T& getComponent(Entity entity) { return getComponentArray<T>()->getData(entity); }

		/// <summary>
		/// Permet de savoir si une entit� poss�de un component de type T
		/// </summary>
		/// <typeparam name="T">Type de component</typeparam>
		/// <param name="entity"></param>
		/// <returns>True si l'entit� poss�de ce component, false sinon</returns>
		template<typename T>
		bool hasComponent(Entity entity) { return getComponentArray<T>()->hasData(entity); }

		/// <summary>
		/// Notifie chaque ComponentArray qu'une entit� a �t� d�truite.
		/// Si il y a un component pour cette entit�, elle est d�truite
		/// </summary>
		/// <param name="entity"></param>
		void entityDestroyed(Entity entity);

};


#endif COMPONENTMANAGER_H