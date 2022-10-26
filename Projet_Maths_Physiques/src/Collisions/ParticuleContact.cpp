#include "Collisions/ParticuleContact.h"

ParticuleContact::~ParticuleContact() {
	delete particules[0];
	delete particules[1];
}

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