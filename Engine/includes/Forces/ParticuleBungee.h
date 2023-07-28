#pragma once
#ifndef PARTICULE_BUNGEE_H
#define PARTICULE_BUNGEE_H

#include "ParticuleForceGenerator.h"

class ParticuleBungee : public ParticuleForceGenerator {

private:
	float _kElasticite;
	Vector3D _attache;
	float _l0;

public:
	ParticuleBungee(float kElasticite, Vector3D attache, Particule* particule, float l0);
	~ParticuleBungee();
	float getkElasticite() { return _kElasticite; };
	Vector3D getAttache() { return _attache; };
	virtual void updateForce(Particule*, float duration);
};

#endif // !PARTICULE_BUNGEE_H