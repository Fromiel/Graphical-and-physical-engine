#pragma once
#ifndef PARTICULE_RESSORT_PTFIXE_H
#define PARTICULE_RESSORT_PTFIXE_H

#include "ParticuleForceGenerator.h"

class ParticuleRessortPtFixe : public ParticuleForceGenerator {
	
private:
	float _kElasticite;
	Vecteur3D _attache;
	float _l0;

public:
	ParticuleRessortPtFixe(float kElasticite, Vecteur3D attache, const Particule& particule);
	~ParticuleRessortPtFixe();
	float getkElasticite() { return _kElasticite; };
	Vecteur3D getAttache() { return _attache; };
	virtual void updateForce(Particule*, float duration);
};

#endif // !PARTICULE_RESSORT_PTFIXE_H
