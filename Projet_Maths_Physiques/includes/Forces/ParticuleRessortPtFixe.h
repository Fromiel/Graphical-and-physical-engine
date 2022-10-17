#pragma once
#ifndef PARTICULE_RESSORT_PTFIXE_H
#define PARTICULE_RESSORT_PTFIXE_H

#include "ParticuleForceGenerator.h"

class ParticuleRessortPtFixe : public ParticuleForceGenerator {
	
private:
	Vecteur3D _forceRessort;
	float _kElasticite;
	Vecteur3D _attache;
	Vecteur3D _l0;

public:
	ParticuleRessortPtFixe(const Vecteur3D&, float kElasticite, Vecteur3D attache, Particule* particule);
	~ParticuleRessortPtFixe();
	Vecteur3D getForceRessort() { return _forceRessort; };
	float getkElasticite() { return _kElasticite; };
	Vecteur3D getAttache() { return _attache; };
	virtual void updateForce(Particule*, float duration);
};




#endif // !PARTICULE_RESSORT_PTFIXE_H
