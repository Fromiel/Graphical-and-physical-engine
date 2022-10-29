#include "Collisions/ParticuleContact.h"

ParticuleContact::~ParticuleContact() {
	delete particules[0];
	delete particules[1];
}

/*ParticuleContact::resolve(float duration) {
	resolveVelocity();
	resolveInterpenetration();
}

float ParticuleContact::calculateSeparatingVelocity() {
	//Différence des 2 vitesses
	Vecteur3D diffVelocity = particules[0]->getVelocity() - particules[1]->getVelocity();
	//On projette sur la normale
	Vecteur3D projVec = scalar_product(diffVelocity, contactNormal) * contactNormal;
	//On renvoie la norme
	return projVec.norm();
}

ParticuleContact::resolveVelocity() {
	float k = calculateK();
	float vp1 = particules[0]->getVelocity() - (k * particules[0]->getInverseMasse() * contactNormal);
	float vp2 = particules[1]->getVelocity() + (k * particules[1]->getInverseMasse() * contactNormal);

	particules[0]->setVelocity(vp1);
	particules[1]->setVelocity(vp2);

}

ParticuleContact::resolveInterpenetration() {
	float ma = 1 / particules[0]->getInverseMasse();
	float mb = 1 / particules[1]->getInverseMasse();
	Vecteur3D pos1 = particules[0]->getPos() + ((mb / (ma + mb) ) * penetration * contactNormal) );
	Vecteur3D pos2 = particules[1]->getPos() - ((ma / (ma + mb)) * penetration * contactNormal) );

	particules[0]->setPos(pos1);
	particules[1]->setPos(pos2);

	//TODO : Contact au repos ?
}

float ParticuleContact::calculateK() const {
	float vreel = calculateSeparatingVelocity();
	return ( (restitution + 1) * vreel) / ((particules[0]->getInverseMasse()) + (particules[1]->getInverseMasse()) );
}*/