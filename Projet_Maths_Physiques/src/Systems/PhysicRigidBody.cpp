#include "Systems/PhysicRigidBody.h"

void PhysicRigidBody::update(float dt)
{
	_registry.updateForces();

	Coordinator* coordinator = Coordinator::getInstance();

	for (auto gameObject : entities_) {

		if (coordinator->hasComponent<Rigidbody>(gameObject)) {
			//std::cout << "\n-------------------------\nGameObject = " << coordinator->getComponentPtr<Rigidbody>(gameObject) << std::endl;
			//std::cout << coordinator->getComponent<Rigidbody>(gameObject).getOrientation() << std::endl;
			coordinator->getComponent<Rigidbody>(gameObject).Integrate(dt);
			//std::cout << "-----------------------------------" << std::endl;
			//coordinator->getComponent<Rigidbody>(gameObject).clearAccumulator();
		}
	}
}