#include "Engines/PhysicalEngine.h"

PhysicalEngine::PhysicalEngine() : coordinator_(Coordinator::getInstance()), physicParticleSystem_(coordinator_->registerSystem<PhysicParticle>()), physicRigidBodySystem_(coordinator_->registerSystem<PhysicRigidBody>())
{
	coordinator_->registerComponent<Transform>();
	coordinator_->registerComponent<Particule>();
	coordinator_->registerComponent<Rigidbody>();

	Signature physicParticleSignature;
	physicParticleSignature.set(coordinator_->getComponentType<Transform>());
	physicParticleSignature.set(coordinator_->getComponentType<Particule>());

	Signature physicRigidBodySignature;
	physicRigidBodySignature.set(coordinator_->getComponentType<Transform>());
	physicRigidBodySignature.set(coordinator_->getComponentType<Rigidbody>());

	coordinator_->setSystemSignature<PhysicParticle>(physicParticleSignature);
	coordinator_->setSystemSignature<PhysicRigidBody>(physicRigidBodySignature);
}

void PhysicalEngine::update(float dt)
{
	physicParticleSystem_->update(dt);
	physicRigidBodySystem_->update(dt);
}