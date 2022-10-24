#include "Forces/ParticuleFriction.h"


void ParticuleFriction::updateForce(Particule* particule, float duration) {
	double v = particule->getVelocity();
	particule->addForce(-1 * v.normalized() * (m_k1 * v + m_k2 * (v*v)));
}