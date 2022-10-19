#include "ParticuleForceRegistry.h"

void ParticuleForceRegistry::add(Particule* particule, ParticuleForceGenerator* fg) {
	ParticuleForceRegistration pfg(particule, fg);
	registre.push_back(pfg);
}

void ParticuleForceRegistry::remove(Particule* particule, ParticuleForceGenerator* fg) {
	for (ParticuleForceRegistration*& pfg : registre) {
		if (pfg->particule == particule && pfg->fg == fg) {
			registre.erase(pfg); //not sure if correct
		}
	}
}

void ParticuleForceRegistry::clear() {
	registre = new Registre;
}

void ParticuleForceRegistry::updateForces(float duration) {
	for (ParticuleForceRegistration*& x : registre) {
		x->fg->updateForce(x->particule, duration);
	}
}