#pragma once
#ifndef FORCE_REGISTRY_H
#define FORCE_REGISTRY_H

#include "ForceGenerator.h"

class ForceRegistry {
public:
	struct ForceRegistration {
		Rigidbody* rigidbody;
		ForceGenerator* fg;
	};
	typedef std::vector<ForceRegistration> RegistreRB;
	void add(Rigidbody*, ForceGenerator*);
	void remove(Rigidbody*, ForceGenerator*);
	void clear();
	void updateForces();
private:
	RegistreRB registre_rb;

};

#endif