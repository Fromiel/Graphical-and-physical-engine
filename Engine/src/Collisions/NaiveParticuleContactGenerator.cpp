#include "Collisions/NaiveParticuleContactGenerator.h"

unsigned int NaiveParticuleContactGenerator::addContact(ParticuleContact* contact, unsigned int limit) const{
	int max_a = -1, max_b = -1;
	float max_penetration = -INFINITY;

	for (int i = 0; i < particules.size(); i++) {
		Vector3D pos_init = particules[i]->getPos();
		for (int j = i; j < particules.size(); j++) {
			float penetration = 2 * radius - ((pos_init - particules[1]->getPos()).norm());
			if (penetration > 0) {
				if (max_penetration < penetration) {
					max_penetration = penetration;
					max_a = i;
					max_b = j;
				}
			}
		}
	}

	if (max_a == -1 || max_b == -1) return 0;

	Vector3D normal_aux;
	if (max_a != -1) { //double check is redundant but improves code visibility during development
		contact->particules[0] = particules[max_a];
		normal_aux = particules[max_a]->getPos();
	}

	if (max_b != -1) {
		contact->particules[1] = particules[max_b];
		normal_aux = normal_aux - particules[max_b]->getPos();
	}

	normal_aux.normalized();

	contact->penetration = max_penetration;
	contact->restitution = 0;
	contact->contactNormal = normal_aux;

	return 1;

}