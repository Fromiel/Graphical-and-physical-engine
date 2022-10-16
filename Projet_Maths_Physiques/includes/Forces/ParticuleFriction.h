#pragma once
#ifndef PARTICULE_FRICTION_H
#define PARTICULE_FRICTION_H

#include "ParticuleForceGenerator.h"

class ParticuleFriction : ParticuleForceGenerator {
public:
	//Constructeur

	ParticuleFriction(const Vecteur3D&);

	//Destructeur

	~ParticuleFriction();

	//Surcharge de la méthode updateForce de ParticuleForceGenerator
	virtual void updateForce(Particule*, float);

private:
	Vecteur3D friction;
};

#endif