#include "CoreECS/Coordinator.h"

Coordinator::Coordinator() : componentManager_(std::make_unique<ComponentManager>()), entityManager_(std::make_unique<EntityManager>()), systemManager_(std::make_unique<SystemManager>())
{

}

Coordinator* Coordinator::instance_ = NULL;

Coordinator* Coordinator::getInstance()
{
	if (instance_ == NULL)
	{
		instance_ = new Coordinator();
	}

	return instance_;
}

// ----------Entity methods-------------------------
Entity Coordinator::createEntity()
{
	return entityManager_->createEntity();
}

void Coordinator::destroyEntity(Entity entity)
{
	entityManager_->destroyEntity(entity);

	componentManager_->entityDestroyed(entity);

	systemManager_->entityDestroyed(entity);
}

