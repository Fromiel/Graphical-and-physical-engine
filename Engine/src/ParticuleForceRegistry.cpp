#include "ParticuleForceRegistry.h"

void ParticuleForceRegistry::add(Particule* particule, ParticuleForceGenerator* fg) {
	ParticuleForceRegistration pfg(particule, fg);
	registre.push_back(pfg);
}

void ParticuleForceRegistry::remove(Particule* particule, ParticuleForceGenerator* fg) {
	int i(0);
	for (ParticuleForceRegistration& pfg : registre) {
		if (pfg.particule == particule && pfg.fg == fg) {
			registre.erase(registre.begin()+i); //not sure if correct
			++i;
		}
	}
}

void ParticuleForceRegistry::clear() {
	registre.clear();
}

void ParticuleForceRegistry::updateForces(float duration) {
	for (ParticuleForceRegistration& x : registre) {
		x.fg->updateForce(x.particule, duration);
	}
}