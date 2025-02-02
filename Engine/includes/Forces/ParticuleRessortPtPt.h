#pragma once
#ifndef PARTICULE_RESSORT_PTPT_H
#define PARTICULE_RESSORT_PTPT_H

#include "ParticuleForceGenerator.h"

class ParticuleRessortPtPt : public ParticuleForceGenerator {

private:
	float _kElasticite;
	Particule* _particuleExt;
	float _l0;

public:
	ParticuleRessortPtPt(float kElasticite, Particule* particule1, Particule* particule2, float l0);
	~ParticuleRessortPtPt();
	float getkElasticite() { return _kElasticite; };
	Vector3D getAttache() { return Vector3D(); }//_attache; };
	virtual void updateForce(Particule*, float duration);
};



#endif // !PARTICULE_RESSORT_PTPT_H
