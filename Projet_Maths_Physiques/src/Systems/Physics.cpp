#include "Systems/Physics.h"
#include "Components.h"

void Physics::update(float dt)
{
	Coordinator* coordinator = Coordinator::getInstance();
	for (auto gameObject : entities_)
	{
		coordinator->getComponent<Particule>(gameObject).update(dt);
		coordinator->getComponent<Particule>(gameObject).clearAccum(); // On clear les accumulateurs de forces car on a pas des forces à ajouter à chaque tour 	}
	}
}