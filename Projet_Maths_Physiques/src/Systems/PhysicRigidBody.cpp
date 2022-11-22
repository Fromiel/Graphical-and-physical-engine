#include "Systems/PhysicRigidBody.h"

void PhysicRigidBody::update(float dt)
{
	_registry.updateForces();

	Coordinator* coordinator = Coordinator::getInstance();

	for (auto gameObject : entities_) {

		std::cout << "GameObject : ";
		std::cout << "Has component ? " << (coordinator->hasComponent<Rigidbody>(gameObject) ? "oui" : "non") << std::endl;


		if (coordinator->hasComponent<Rigidbody>(gameObject)) {

			std::cout << "In If condition" << std::endl;

			coordinator->getComponent<Rigidbody>(gameObject).Integrate(dt);
			coordinator->getComponent<Rigidbody>(gameObject).clearAccumulator();
		}
	}
}