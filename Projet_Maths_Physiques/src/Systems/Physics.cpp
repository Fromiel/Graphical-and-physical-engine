#include "Systems/Physics.h"
#include "Components.h"

void Physics::update(float dt)
{
	Coordinator* coordinator = Coordinator::getInstance();
	for (auto gameObject : entities_)
	{
		coordinator->getComponent<Particule>(gameObject).update(dt);
		auto newPosition = coordinator->getComponent<Particule>(gameObject).getPos();
		coordinator->getComponent<Transform>(gameObject).setPosition(newPosition);
	}
}