#include "Collisions/ParticuleLink.h"

float ParticuleLink::currentLength() const {
	if (particules[0] && particules[1]) {
		return Vector3D::distance(particules[0]->getPos(), particules[1]->getPos());
	}
	else {
		return 0;
	}
}