#ifndef COMPONENTARRAY_H
#define COMPONENTARRAY_H

#include "CoreECS/ECS.h"
#include <array>
#include <unordered_map>
#include <assert.h> 


/// <summary>
/// Cette interface permet au ComponentManager d'informer n'importe quel ComponentArray qu'une entité est détruite et qu'elle doit mettre à jour sa map
/// </summary>
class IComponentArray
{
public:
	/// <summary>
	/// Destructeur de IComponentArray
	/// </summary>
	virtual ~IComponentArray() = default;


	/// <summary>
	/// Méthode à appeler lorsque une entité est détruite
	/// </summary>
	/// <param name="entity"></param>
	virtual void entityDestroyed(Entity entity) = 0;
};


/// <summary>
/// Classe représentant un tableau dense de components chacun lié à une entité
/// </summary>
template<typename T>
class ComponentArray : public IComponentArray
{
	private:
		// Le tableau stacké de components,mis à un indice maximal spécifié (le maximum d'entités autorisées) pour que chaque entité n'ai qu'une seule place
		std::array<T, MAX_ENTITIES> componentArray_ {};

		// Map de l'id d'une entité vers l'indice du tableau
		std::unordered_map<Entity, size_t> entityToIndexMap_{};

		// Map de l'indice du tableau vers l'id d'une entité
		std::unordered_map<size_t, Entity> indexToEntityMap_{};

		// Nombre d'entrés valides dans le tableau
		size_t size_;

	public:
		/// <summary>
		/// Constructeur de ComponentArray initialisant size_ à 0
		/// </summary>
		/// <typeparam name="T"></typeparam>
		ComponentArray() : size_(0) {}

		/// <summary>
		/// On ajoute un component à une entité
		/// </summary>
		/// <param name="entity">L'entité à laquelle on ajoute le component</param>
		/// <param name="component">Composant à ajouter</param>
		void insertData(Entity entity, T component)
		{
			assert(entityToIndexMap_.find(entity) == entityToIndexMap_.end() && "Component added to same entity more than once.");

			// Ajoute une nouvelle entrée à la fin du tableau et met à jour la map
			size_t newIndex = size_;
			entityToIndexMap_[entity] = newIndex;
			indexToEntityMap_[newIndex] = entity;
			componentArray_[newIndex] = component;
			size_++;
		}

		/// <summary>
		/// Supprime l'entité passée en argument ainsi que son composant
		/// </summary>
		/// <param name="entity"></param>
		void removeData(Entity entity)
		{
			assert(entityToIndexMap_.find(entity) != entityToIndexMap_.end() && "Removing non-existent component.");

			// Copie les éléments à la fin du tableau à la place des éléments supprimés pour maintenir la densité du tableau
			size_t indexOfRemovedEntity = entityToIndexMap_[entity];
			size_t indexOfLastElement = size_ - 1;
			componentArray_[indexOfRemovedEntity] = componentArray_[indexOfLastElement];

			// Met à jour la map pour les éléments déplacés
			Entity entityOfLastElement = indexToEntityMap_[indexOfLastElement];
			entityToIndexMap_[entityOfLastElement] = indexOfRemovedEntity;
			indexToEntityMap_[indexOfRemovedEntity] = entityOfLastElement;

			entityToIndexMap_.erase(entity);
			indexToEntityMap_.erase(indexOfLastElement);

			size_--;
		}

		/// <summary>
		/// Permet d'obtenir le component lié à l'entité passée en argument
		/// </summary>
		/// <param name="entity"></param>
		/// <returns></returns>
		T& getData(Entity entity)
		{
			assert(entityToIndexMap_.find(entity) != entityToIndexMap_.end() && "Retrieving non-existent component.");

			// Retourne une référence au component de l'entité
			return componentArray_[entityToIndexMap_[entity]];
		}

		/// <summary>
		/// Permet de savoir si une entité possède un component de ce type
		/// </summary>
		/// <param name="entity"></param>
		/// <returns>True si l'entité possède ce component, false sinon</returns>
		bool hasData(Entity entity) { return entityToIndexMap_.find(entity) != entityToIndexMap_.end(); }

		/// <summary>
		/// Méthode à appeler lorsque une entité est détruite
		/// </summary>
		/// <param name="entity"></param>
		void entityDestroyed(Entity entity) override
		{
			if (entityToIndexMap_.find(entity) != entityToIndexMap_.end())
			{
				// Supprime le component de l'entité si il existe
				removeData(entity);
			}
		}

};


#endif