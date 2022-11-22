#include "Forces/ForceRegistry.h"

void ForceRegistry::add(Rigidbody* rb, ForceGenerator* fg) {
	ForceRegistration f_regist(rb, fg);
	registre_rb.push_back(f_regist);
}

void ForceRegistry::remove(Rigidbody* rb, ForceGenerator* fg) {
	int i(0);
	for (ForceRegistration& fr : registre_rb) {
		if (fr.rigidbody == rb && fr.fg == fg) {
			registre_rb.erase(registre_rb.begin() + i); //not sure if correct
			++i;
		}
	}
}

void ForceRegistry::clear() {
	registre_rb.clear();
}

void ForceRegistry::updateForces() {
	for (ForceRegistration& fr : registre_rb) {
		fr.fg->UpdateForce(fr.rigidbody);
	}
}