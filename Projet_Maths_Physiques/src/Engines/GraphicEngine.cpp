#include "Engines/GraphicEngine.h"


GraphicEngine::GraphicEngine() : coordinator_(Coordinator::getInstance()), renderSystem_(coordinator_->registerSystem<Render>())
{
	coordinator_->registerComponent<Transform>();
	coordinator_->registerComponent<Object3D>();
	coordinator_->registerComponent<Light>();
	coordinator_->registerComponent<Camera>();
	coordinator_->registerComponent<Material>();

	Signature renderSignature;
	renderSignature.set(coordinator_->getComponentType<Transform>());

	coordinator_->setSystemSignature<Render>(renderSignature);
}

void GraphicEngine::update(float dt)
{
	renderSystem_->update(dt);
}