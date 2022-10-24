#include "Collisions/ParticuleContact.h"

ParticuleContact::resolve(float duration) {
	//TODO
}

ParticuleContact::calculateSeparatingVelocity() {
	return -restitution * particules[0]->getVelocity();
}

ParticuleContact::resolveVelocity() {
	//TODO
}

ParticuleContact::resolveInterpenetration() {
	//TODO
}