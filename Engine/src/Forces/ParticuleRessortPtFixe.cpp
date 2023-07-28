#include "Forces/ParticuleRessortPtFixe.h"

ParticuleRessortPtFixe::ParticuleRessortPtFixe(float kElasticite, Vector3D attache, const Particule& particule, float l0) {
	_kElasticite = kElasticite;
	_attache = attache;
	_l0 = l0;
}

ParticuleRessortPtFixe::~ParticuleRessortPtFixe() {
	
}

void ParticuleRessortPtFixe::updateForce(Particule* particule, float duration) {
	Vector3D direction = particule->getPos() - _attache;
	direction = direction.normalized();
	float l = Vector3D::distance(particule->getPos(), _attache);
	particule->addForce((-_kElasticite * (l - _l0))*direction);
};