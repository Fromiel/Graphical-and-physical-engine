#include "Forces/ParticuleFriction.h"

ParticuleFriction::ParticuleFriction(const Vecteur3D& f = Vecteur3D(0,0,0)) {
	friction = Vecteur3D(f);
}

ParticuleFriction::~ParticuleFriction() {}

void ParticuleFriction::updateForce(Particule* particule, float duration) {
	particule->addForce();
}