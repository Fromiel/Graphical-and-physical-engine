#include "Engine.h"

Engine::Engine() : inputManager_(), time_()
{
	graphicEngine_ = new GraphicEngine();
	physicalEngine_ = new PhysicalEngine();
	logicEngine_ = new LogicEngine();
	inputManager_.setupKeyInputs(graphicEngine_->getRenderSystem()->getWindow());
}

Engine* Engine::instance_ = NULL;

Engine* Engine::getInstance()
{
	if (instance_ == NULL)
	{
		instance_ = new Engine();
	}

	return instance_;
}

void Engine::loop()
{
	//Start du logicengine
	logicEngine_->start();

	while (!inputManager_.endGame())
	{
		//update clock
		time_.update();
		float dt = time_.deltaTime();

		if (dt > 0)
		{
			//Logic
			logicEngine_->update(dt);

			//Physical simulation
			physicalEngine_->update(dt);

		}
		else
		{
			logicEngine_->update(time_.forcedDeltaTime());
		}

		//render
		graphicEngine_->update(dt);

		//process events
		inputManager_.pollEvents();
	}
}