#pragma once
#ifndef PARTICULE_BUNGEE_H
#define PARTICULE_BUNGEE_H

#include "ParticuleForceGenerator.h"

class ParticuleBungee : public ParticuleForceGenerator {

private:
	float _kElasticite;
	Vecteur3D _attache;
	float _l0;

public:
	ParticuleBungee(float kElasticite, Vecteur3D attache, Particule* particule);
	~ParticuleBungee();
	float getkElasticite() { return _kElasticite; };
	Vecteur3D getAttache() { return _attache; };
	virtual void updateForce(Particule*, float duration);
};

#endif // !PARTICULE_BUNGEE_H