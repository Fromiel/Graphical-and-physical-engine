#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "ComponentArray.h"
#include <memory>

/// <summary>
/// Classe faisant le lien entre tous les différents ComponentArrays lorsqu'un composant doit être ajouté ou supprimé
/// </summary>
class ComponentManager
{
	private:
		// Map d'un pointeur de string vers un component
		std::unordered_map<const char*, ComponentType> componentTypes_;

		// Map d'un pointeur de string vers un ComponentArray
		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays_;

		// Le type de component qui doit être enregistré à l'ajout du prochain component (en commencant à 0)
		ComponentType nextComponentType_;

		// Fonction utilisée pour obtenir le pointeur vers un ComponentArray qu'on a caster vers le type ComponentArray<T>
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

			// Ajoute ce type de component à la map de components
			componentTypes_.insert({ typeName, nextComponentType_ });

			// Créé un pointeur de ComponentArray et l'ajoute à la map de ComponentArrays
			componentArrays_.insert({ typeName, std::make_shared<ComponentArray<T>>() });

			// Incrément la valeur pour que le prochain component qui sera ajouté aura un type différent
			nextComponentType_++;
		}

		/// <summary>
		/// Retourne le type du component T (utilisé pour créer les signatures)
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
		/// Ajoute un component T pour une entité donnée à son ComponentArray associé
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="entity"></param>
		/// <param name="component"></param>
		template<typename T>
		void addComponent(Entity entity, T component) { getComponentArray<T>()->insertData(entity, component); }

		/// <summary>
		/// Enlève un component T pour une entité donnée à son ComponentArray associé
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="entity"></param>
		template<typename T>
		void removeComponent(Entity entity) { getComponentArray<T>()->removeData(entity); }

		/// <summary>
		/// Retourne une référence vers un component T de l'entité passée en argument
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="entity"></param>
		/// <returns></returns>
		template<typename T>
		T& getComponent(Entity entity) { return getComponentArray<T>()->getData(entity); }

		/// <summary>
		/// Permet de savoir si une entité possède un component de type T
		/// </summary>
		/// <typeparam name="T">Type de component</typeparam>
		/// <param name="entity"></param>
		/// <returns>True si l'entité possède ce component, false sinon</returns>
		template<typename T>
		bool hasComponent(Entity entity) { return getComponentArray<T>()->hasData(entity); }

		/// <summary>
		/// Notifie chaque ComponentArray qu'une entité a été détruite.
		/// Si il y a un component pour cette entité, elle est détruite
		/// </summary>
		/// <param name="entity"></param>
		void entityDestroyed(Entity entity);

};


#endif COMPONENTMANAGER_H