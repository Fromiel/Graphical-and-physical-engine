#pragma once
#ifndef PARTICULE_GRAVITY_H
#define PARTICULE_GRAVITY_H

#include "ParticuleForceGenerator.h"

class ParticuleGravity : public ParticuleForceGenerator {
public:
	//Constructeurs

	ParticuleGravity(const Vecteur3D&);
	ParticuleGravity(float);

	//Destructeur
	
		~ParticuleGravity();

	//Override de la m�thode updateForce de la classe ParticleForceGenerator
	virtual void updateForce(Particule*, float);
private:
	Vecteur3D gravity;
};

#endif