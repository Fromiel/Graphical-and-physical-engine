#include "Forces/ParticuleRessortPtPt.h"

ParticuleRessortPtPt::ParticuleRessortPtPt(float kElasticite, Particule* particule1, Particule* particule2) {
	_kElasticite = kElasticite;
	_particuleExt = particule2;
	_l0 = distance(particule1->getPos(), particule2->getPos());
}

ParticuleRessortPtPt::~ParticuleRessortPtPt() {

}

void ParticuleRessortPtPt::updateForce(Particule* particule, float duration) {
	Vecteur3D direction = particule->getPos() - _particuleExt->getPos();
	direction = direction.normalized();
	float l = distance(particule->getPos(), _particuleExt->getPos());
	particule->addForce((_kElasticite * (l - _l0))*direction);
}