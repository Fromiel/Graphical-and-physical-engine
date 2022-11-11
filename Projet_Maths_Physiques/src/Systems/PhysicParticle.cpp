#include "Systems/PhysicParticle.h"
#include "Components.h"

PhysicParticle::PhysicParticle() : forceRegistry_(ParticuleForceRegistry())
{
	particleContact_ = new ParticuleContact();
}

void PhysicParticle::update(float dt)
{
	allContactsInScene_.clear();

	particleContact_->clear();

	for (auto& cable : cables_)
	{
		cable.addContact(particleContact_, 0);
	}

	for (auto& rod : rods_)
	{
		rod.addContact(particleContact_, 0);
	}

	allContactsInScene_.push_back(particleContact_);

	contactResolver_.SetIterations(1 + static_cast<unsigned int>(allContactsInScene_.size()) * 2);
	contactResolver_.resolveContacts(allContactsInScene_, 1, dt);

	Coordinator* coordinator = Coordinator::getInstance();

	forceRegistry_.updateForces(dt);

	for (auto gameObject : entities_)
	{
		coordinator->getComponent<Particule>(gameObject).update(dt);
		coordinator->getComponent<Particule>(gameObject).clearAccum(); // On clear les accumulateurs de forces car on a pas des forces à ajouter à chaque tour 	}
	}
}