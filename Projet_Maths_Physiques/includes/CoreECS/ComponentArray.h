#ifndef COMPONENTARRAY_H
#define COMPONENTARRAY_H

#include "CoreECS/ECS.h"
#include <array>
#include <unordered_map>
#include <assert.h> 


/// <summary>
/// Cette interface permet au ComponentManager d'informer n'importe quel ComponentArray qu'une entit� est d�truite et qu'elle doit mettre � jour sa map
/// </summary>
class IComponentArray
{
public:
	/// <summary>
	/// Destructeur de IComponentArray
	/// </summary>
	virtual ~IComponentArray() = default;


	/// <summary>
	/// M�thode � appeler lorsque une entit� est d�truite
	/// </summary>
	/// <param name="entity"></param>
	virtual void entityDestroyed(Entity entity) = 0;
};


/// <summary>
/// Classe repr�sentant un tableau dense de components chacun li� � une entit�
/// </summary>
template<typename T>
class ComponentArray : public IComponentArray
{
	private:
		// Le tableau stack� de components,mis � un indice maximal sp�cifi� (le maximum d'entit�s autoris�es) pour que chaque entit� n'ai qu'une seule place
		std::array<T, MAX_ENTITIES> componentArray_ {};

		// Map de l'id d'une entit� vers l'indice du tableau
		std::unordered_map<Entity, size_t> entityToIndexMap_{};

		// Map de l'indice du tableau vers l'id d'une entit�
		std::unordered_map<size_t, Entity> indexToEntityMap_{};

		// Nombre d'entr�s valides dans le tableau
		size_t size_;

	public:
		/// <summary>
		/// Constructeur de ComponentArray initialisant size_ � 0
		/// </summary>
		/// <typeparam name="T"></typeparam>
		ComponentArray() : size_(0) {}

		/// <summary>
		/// On ajoute un component � une entit�
		/// </summary>
		/// <param name="entity">L'entit� � laquelle on ajoute le component</param>
		/// <param name="component">Composant � ajouter</param>
		void insertData(Entity entity, T component)
		{
			assert(entityToIndexMap_.find(entity) == entityToIndexMap_.end() && "Component added to same entity more than once.");

			// Ajoute une nouvelle entr�e � la fin du tableau et met � jour la map
			size_t newIndex = size_;
			entityToIndexMap_[entity] = newIndex;
			indexToEntityMap_[newIndex] = entity;
			componentArray_[newIndex] = component;
			size_++;
		}

		/// <summary>
		/// Supprime l'entit� pass�e en argument ainsi que son composant
		/// </summary>
		/// <param name="entity"></param>
		void removeData(Entity entity)
		{
			assert(entityToIndexMap_.find(entity) != entityToIndexMap_.end() && "Removing non-existent component.");

			// Copie les �l�ments � la fin du tableau � la place des �l�ments supprim�s pour maintenir la densit� du tableau
			size_t indexOfRemovedEntity = entityToIndexMap_[entity];
			size_t indexOfLastElement = size_ - 1;
			componentArray_[indexOfRemovedEntity] = componentArray_[indexOfLastElement];

			// Met � jour la map pour les �l�ments d�plac�s
			Entity entityOfLastElement = indexToEntityMap_[indexOfLastElement];
			entityToIndexMap_[entityOfLastElement] = indexOfRemovedEntity;
			indexToEntityMap_[indexOfRemovedEntity] = entityOfLastElement;

			entityToIndexMap_.erase(entity);
			indexToEntityMap_.erase(indexOfLastElement);

			size_--;
		}

		/// <summary>
		/// Permet d'obtenir le component li� � l'entit� pass�e en argument
		/// </summary>
		/// <param name="entity"></param>
		/// <returns></returns>
		T& getData(Entity entity)
		{
			assert(entityToIndexMap_.find(entity) != entityToIndexMap_.end() && "Retrieving non-existent component.");

			// Retourne une r�f�rence au component de l'entit�
			return componentArray_[entityToIndexMap_[entity]];
		}

		/// <summary>
		/// Permet de savoir si une entit� poss�de un component de ce type
		/// </summary>
		/// <param name="entity"></param>
		/// <returns>True si l'entit� poss�de ce component, false sinon</returns>
		bool hasData(Entity entity) { return entityToIndexMap_.find(entity) != entityToIndexMap_.end(); }

		/// <summary>
		/// M�thode � appeler lorsque une entit� est d�truite
		/// </summary>
		/// <param name="entity"></param>
		void entityDestroyed(Entity entity) override
		{
			if (entityToIndexMap_.find(entity) != entityToIndexMap_.end())
			{
				// Supprime le component de l'entit� si il existe
				removeData(entity);
			}
		}

};


#endif