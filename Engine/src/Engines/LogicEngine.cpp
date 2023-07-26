#include "Engines/LogicEngine.h"
#include "Components/LogicBehaviour.h"

LogicEngine::LogicEngine() : coordinator_(Coordinator::getInstance()), logicSystem_(coordinator_->registerSystem<Logic>())
{
	coordinator_->registerComponent<LogicBehaviour>();

	Signature logicSignature;
	logicSignature.set(coordinator_->getComponentType<LogicBehaviour>());

	coordinator_->setSystemSignature<Logic>(logicSignature);
}

void LogicEngine::update(float dt)
{
	logicSystem_->update(dt);
}

void LogicEngine::start()
{
	logicSystem_->start();
}