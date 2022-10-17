#include "Forces/ParticuleRessortPtPt.h"

ParticuleRessortPtPt::ParticuleRessortPtPt(const Vecteur3D& vect, float kElasticite, Particule* particule1, Particule* particule2) {
	_forceRessort = Vecteur3D(vect);
	_kElasticite = kElasticite;
	_particuleExt = particule2;
	_l0 = distance(particule1->getPos, particule2->getPos);
}

ParticuleRessortPtPt::~ParticuleRessortPtPt() {

}

virtual void ParticuleRessortPtPt::updateForce(Particule* particule, float duration) {
	float l = distance(particule->getPos, _particuleExt->getPos);
	particule->addForce(_kElasticite * (l - _l0));
}