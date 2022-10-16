#pragma once
#ifndef PARTICULE_FORCE_REGISTRY_H
#define PARTICULE_FORCE_REGISTRY_H

#include "Particule.h"
#include "ParticuleForceGenerator.h"

#include <vector>

class ParticuleForceRegistry {
public:

	//Constructeurs TODO

	//Destructeur TODO

	//Strucut pour les éléments du registre
	struct ParticuleForceRegistration {
		Particule* particule;
		ParticuleForceGenerator* fg;
	};
	typedef std::vector<ParticuleForceRegistration> Registre;

	void add(Particule*, ParticuleForceGenerator*);
	void remove(Particule*, ParticuleForceGenerator*);
	void clear();
	void updateForces(float);

private:
	Registre registre;
};

#endif