#include "CoreECS/SystemManager.h"


void SystemManager::entityDestroyed(Entity entity)
{
	for (auto const& pair : systems_)
	{
		auto const& system = pair.second;

		system->eraseEntity(entity);
	}
}

void SystemManager::entitySignatureChanged(Entity entity, Signature entitySignature)
{
	for (auto const& pair : systems_)
	{
		auto const& type = pair.first;
		auto const& system = pair.second;
		auto const& systemSignature = signatures_[type];

		// Si la signature de l'entité vaut celle du système, on l'ajoute dans l'ensemble d'entités du système
		if ((entitySignature & systemSignature) == systemSignature)
		{
			system->insertEntity(entity);
		}
		// Si la signature de l'entité ne vaut pas celle du système, on la supprime de l'ensemble d'entités du système
		else
		{
			system->eraseEntity(entity);
		}
	}
}