#include "Forces/ParticuleGravity.h"

void ParticuleGravity::updateForce(Particule* particule, float duration) {
	float imasse = particule->getInverseMasse();
	if (imasse < DBL_MAX) {
		float masse = (imasse == 0 ? 0 : 1 / imasse);
		particule->addForce(masse * gravity);
	}
}

ParticuleGravity::ParticuleGravity(const Vecteur3D& g = Vecteur3D(0.0f, -9.81f, 0.0f)) {
	gravity = Vecteur3D(g);
}

ParticuleGravity::ParticuleGravity(float g) {
	gravity = Vecteur3D(0, g, 0);
}

ParticuleGravity::~ParticuleGravity(){}