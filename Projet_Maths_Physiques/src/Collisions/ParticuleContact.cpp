#include "Collisions/ParticuleContact.h"

ParticuleContact::~ParticuleContact() {
	delete particules[0];
	delete particules[1];
}

void ParticuleContact::resolve(float duration) { 
	resolveVelocity();
	resolveInterpenetration();
}

float ParticuleContact::calculateSeparatingVelocity() const {
	//Différence des 2 vitesses
	Vecteur3D diffVelocity = particules[0]->getVelocity() - (particules[1] ? particules[1]->getVelocity() : 0);
	//On projette sur la normale
	Vecteur3D projVec = diffVelocity * contactNormal;
	//On renvoie la norme
	return projVec.norm();
}

void ParticuleContact::resolveVelocity() {
	float k = calculateK();
	Vecteur3D vp1 = particules[0]->getVelocity() - (k * particules[0]->getInverseMasse() * contactNormal);
	Vecteur3D vp2 = particules[1]->getVelocity() + (k * particules[1]->getInverseMasse() * contactNormal);

	particules[0]->setVelocity(vp1);
	particules[1]->setVelocity(vp2);

}

void ParticuleContact::resolveInterpenetration() {
	if (penetration < 0) return; //on skip si on a pas d'interpénétration

	float ma = 1 / particules[0]->getInverseMasse();
	float mb = (particules[1] ? 1 / particules[1]->getInverseMasse() : 0);
	Vecteur3D pos1 = particules[0]->getPos() + ((mb / (ma + mb) ) * penetration * contactNormal) ;

	if (particules[1]) {
		Vecteur3D pos2 = particules[1]->getPos() - ((ma / (ma + mb)) * penetration * contactNormal);
		particules[1]->setPos(pos2);
	}
	particules[0]->setPos(pos1);
	

	//TODO : Contact au repos ?
}

float ParticuleContact::calculateK() const {
	float vreel = calculateSeparatingVelocity();
	return ( (restitution + 1) * vreel) / ((particules[0]->getInverseMasse()) + (particules[1]->getInverseMasse()) );
}

bool operator<(const ParticuleContact& p1, const ParticuleContact& p2) {
	return 0;
}