#include "Forces/ParticuleFriction.h"

ParticuleFriction::ParticuleFriction(const Vecteur3D& f = Vecteur3D(0,0,0)) {
	friction = Vecteur3D(f);
}

ParticuleFriction::~ParticuleFriction() {}

void ParticuleFriction::updateForce(Particule* particule, float duration) {
	double v = particule->getVelocity();
	//WARNING : Intégration avec des forces nulles pour le moment
	if (v == 0) { //Cas friction statique
		particule->addForce(Vecteur3D(0,0,0));
	}
	else { //Cas friction cinétique
		particule->addForce(Vecteur3D(0,0,0));
	}
}