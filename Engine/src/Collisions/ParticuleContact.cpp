#include "Collisions/ParticuleContact.h"

ParticuleContact::~ParticuleContact() {
	delete particules[0];
	delete particules[1];
}

void ParticuleContact::resolve(float duration) {
	if (particules[0]) {
		resolveVelocity(duration);
		resolveInterpenetration();
	}
}

float ParticuleContact::calculateSeparatingVelocity() const {
	//Différence des 2 vitesses
	Vector3D diffVelocity = (particules[0] ? particules[0]->getVelocity() : 0) - (particules[1] ? particules[1]->getVelocity() : 0);
	//On projette sur la normale
	float projVec = Vector3D::scalar_product(diffVelocity,contactNormal);
	//On renvoie la norme
	return projVec;
}

void ParticuleContact::resolveVelocity(float duration) {
	float k = calculateK(duration);
	Vector3D vp1, vp2;
	if (particules[0]) vp1 = particules[0]->getVelocity() - (k * particules[0]->getInverseMasse() * contactNormal);
	if (particules[1]) vp2 = particules[1]->getVelocity() + (k * particules[1]->getInverseMasse() * contactNormal);

	if (particules[0]) particules[0]->setVelocity(vp1);
	if (particules[1]) particules[1]->setVelocity(vp2);

}

void ParticuleContact::resolveInterpenetration() {
	if (penetration < 0) return; //on skip si on a pas d'interpénétration

	float ma = 1 / particules[0]->getInverseMasse();
	float mb = (particules[1] ? 1 / particules[1]->getInverseMasse() : 0);
	Vector3D pos1 = particules[0]->getPos() - ((mb / (ma + mb) ) * penetration * contactNormal) ;

	if (particules[1]) {
		Vector3D pos2 = particules[1]->getPos() + ((ma / (ma + mb)) * penetration * contactNormal);
		particules[1]->setPos(pos2);
	}
	particules[0]->setPos(pos1);
	
}

float ParticuleContact::calculateK(float duration) const {
	float vreel = calculateSeparatingVelocity();

	//resting contacts handling//

	Vector3D accCausedVelocity = particules[0]->getAcc();
	if (particules[1]) accCausedVelocity = accCausedVelocity - particules[1]->getAcc();
	float accCausedSepVelocity = Vector3D::scalar_product(accCausedVelocity,contactNormal) * duration;
	if (accCausedSepVelocity < 0) {
		vreel += accCausedSepVelocity * duration;

		if (vreel < 0) vreel = 0;
	}

	//--------------------------//

	return ( (restitution + 1) * vreel) / ((particules[0]->getInverseMasse()) + (particules[1] ? particules[1]->getInverseMasse() : 0) );
}

void ParticuleContact::clear() {
	particules[0] = nullptr;
	particules[1] = nullptr;
	restitution = 0;
	penetration = 0;
	contactNormal = Vector3D();
}

bool operator<(const ParticuleContact& p1, const ParticuleContact& p2) {
	return 0;
}