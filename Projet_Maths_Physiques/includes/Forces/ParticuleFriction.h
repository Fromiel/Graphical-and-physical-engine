#pragma once
#ifndef PARTICULE_FRICTION_H
#define PARTICULE_FRICTION_H

#include "ParticuleForceGenerator.h"

class ParticuleFriction : ParticuleForceGenerator {
public:
	//Constructeur

	ParticuleFriction(float k1 = 0, float k2 = 0) :m_k1(k1), m_k2(k2) {}

	//Destructeur

	~ParticuleFriction() {}

	//Surcharge de la méthode updateForce de ParticuleForceGenerator
	virtual void updateForce(Particule*, float);

private:
	float m_k1;
	float m_k2;
};

#endif