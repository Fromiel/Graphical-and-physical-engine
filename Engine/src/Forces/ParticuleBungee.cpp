#include "Forces/ParticuleBungee.h"
#include <cmath>

ParticuleBungee::ParticuleBungee(float kElasticite, Vector3D attache, Particule* particule, float l0) {
	_kElasticite = kElasticite;
	_attache = attache;
	_l0 = l0;
}

ParticuleBungee::~ParticuleBungee() {

}

void ParticuleBungee::updateForce(Particule* particule, float duration) {
	Vector3D direction = particule->getPos() - _attache;
	direction = direction.normalized();
	float l = Vector3D::distance(particule->getPos(), _attache);
	if (l < abs(_l0)) {
		particule->addForce(Vector3D(0,0,0));
	}
	else {
		particule->addForce((-_kElasticite * (l - _l0)) * direction);
	}
};