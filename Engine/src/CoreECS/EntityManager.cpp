#include "CoreECS/EntityManager.h"


EntityManager::EntityManager() : livingEntityCount_(0)
{
	// Initialise la file avec toutes les ids possibles
	for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
	{
		availableEntities_.push(entity);
	}
}

Entity EntityManager::createEntity()
{
	assert(livingEntityCount_ < MAX_ENTITIES && "Too many entities in existence.");

	// Prend un ID sur le devant de la file
	Entity id = availableEntities_.front();
	availableEntities_.pop();
	livingEntityCount_++;

	return id;
}

void EntityManager::destroyEntity(Entity entity)
{
	assert(entity < MAX_ENTITIES && "Entity out of range.");

	// Invalide la signature de l'entité détruite
	signatures_[entity].reset();

	// Met l'id de l'entité détruite au bout de la file
	availableEntities_.push(entity);
	livingEntityCount_--;
}

void EntityManager::setSignature(Entity entity, Signature signature)
{
	assert(entity < MAX_ENTITIES && "Entity out of range.");

	// Met le signature de cette entité dans un tableau
	signatures_[entity] = signature;
}

Signature EntityManager::getSignature(Entity entity)
{
	assert(entity < MAX_ENTITIES && "Entity out of range.");

	return signatures_[entity];
}