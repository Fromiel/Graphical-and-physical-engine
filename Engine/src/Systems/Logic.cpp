#include "Systems/Logic.h"
#include "CoreECS/Coordinator.h"
#include "Components/LogicBehaviour.h"


void Logic::start()
{
	Coordinator* coordinator = Coordinator::getInstance();
	for (auto logicObject : entities_)
	{
		coordinator->getComponent<LogicBehaviour>(logicObject).start();
	}
}

void Logic::update(float dt)
{
	Coordinator* coordinator = Coordinator::getInstance();
	for (auto logicObject : entities_)
	{
		coordinator->getComponent<LogicBehaviour>(logicObject).update(dt);
	}
}