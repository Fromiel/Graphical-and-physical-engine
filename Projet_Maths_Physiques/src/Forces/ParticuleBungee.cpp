#include "Forces/ParticuleBungee.h"

ParticuleBungee::ParticuleBungee(float kElasticite, Vecteur3D attache, Particule* particule) {
	_kElasticite = kElasticite;
	_attache = attache;
	_l0 = distance(particule->getPos, attache);
}

ParticuleBungee::~ParticuleBungee() {

}

virtual void ParticuleBungee::updateForce(Particule* particule, float duration) {
	Vecteur3D direction = particule->getPos - _attache;
	direction = direction.normalized();
	float l = distance(particule->getPos, _attache);
	if (l < _l0) {
		return;
	}
	else {
		particule->addForce((_kElasticite * (l - _l0)) * direction);
	}
};