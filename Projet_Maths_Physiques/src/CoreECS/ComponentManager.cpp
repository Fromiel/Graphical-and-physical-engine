#include "CoreECS/ComponentManager.h"

void ComponentManager::entityDestroyed(Entity entity)
{
	for (auto const& pair : componentArrays_)
	{
		auto const& component = pair.second;

		component->entityDestroyed(entity);
	}
}