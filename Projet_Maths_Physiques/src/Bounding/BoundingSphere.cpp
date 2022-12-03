#include "Bounding/BoundingSphere.h"

BoundingSphere::BoundingSphere(const BoundingSphere& bs1, const BoundingSphere& bs2) {
	Vecteur3D center_offset = bs1.center - bs2.center;
	float distance = center_offset.norm_squared();
	float radiusDiff = bs2.radius - bs1.radius;

	//On vérifie l'encapsulage
	if (radiusDiff * radiusDiff >= distance) { //L'une des sphère intègre l'autre
		if (bs1.radius > bs2.radius) {
			center = bs1.center;
			radius = bs1.radius;
		}
		else {
			center = bs2.center;
			radius = bs2.radius;
		}
	}
	else { //Sinon on calcule notre sphère qui englobe les 2

		//Nouveau rayon
		distance = sqrt(distance);
		radius = (distance + bs1.radius + bs2.radius) / 2;

		//Nouveau centre : on se déplace du premier vers le second
		center = bs1.center;
		if (distance > 0) {
			center = center + center_offset * ((radius - bs1.radius) / distance);
		}
	}
}

bool BoundingSphere::overlaps(const BoundingSphere* other) const {
	float distanceCarre = (center - (other)->center).norm_squared();
	float sumRadius = radius + (other)->radius;
	return distanceCarre < (sumRadius * sumRadius);
}

float BoundingSphere::getSize() const {
	//TODO
	return 0;
}