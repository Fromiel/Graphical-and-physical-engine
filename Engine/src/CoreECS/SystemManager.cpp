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

		// Si la signature de l'entit� vaut celle du syst�me, on l'ajoute dans l'ensemble d'entit�s du syst�me
		if ((entitySignature & systemSignature) == systemSignature)
		{
			system->insertEntity(entity);
		}
		// Si la signature de l'entit� ne vaut pas celle du syst�me, on la supprime de l'ensemble d'entit�s du syst�me
		else
		{
			system->eraseEntity(entity);
		}
	}
}