#include "Forces/ParticuleBungee.h"

ParticuleBungee::ParticuleBungee(float kElasticite, Vecteur3D attache, Particule* particule, float l0) {
	_kElasticite = kElasticite;
	_attache = attache;
	_l0 = l0;
}

ParticuleBungee::~ParticuleBungee() {

}

void ParticuleBungee::updateForce(Particule* particule, float duration) {
	Vecteur3D direction = particule->getPos() - _attache;
	direction = direction.normalized();
	float l = distance(particule->getPos(), _attache);
	if (l < _l0) {
		particule->addForce(Vecteur3D(0,0,0));
	}
	else {
		particule->addForce((-_kElasticite * (l - _l0)) * direction);
	}
};