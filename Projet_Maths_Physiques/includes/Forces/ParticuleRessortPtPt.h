#pragma once
#ifndef PARTICULE_RESSORT_PTPT_H
#define PARTICULE_RESSORT_PTPT_H

#include "ParticuleForceGenerator.h"

class ParticuleRessortPtPt : public ParticuleForceGenerator {

private:
	Vecteur3D _forceRessort;
	float _kElasticite;
	Particule* _particuleExt;
	Vecteur3D _l0;

public:
	ParticuleRessortPtPt(const Vecteur3D&, float kElasticite, Particule* particule1, Particule* particule2);
	~ParticuleRessortPtPt();
	Vecteur3D getForceRessort() { return _forceRessort; };
	float getkElasticite() { return _kElasticite; };
	Vecteur3D getAttache() { return _attache; };
	virtual void updateForce(Particule*, float duration);
};



#endif // !PARTICULE_RESSORT_PTPT_H
