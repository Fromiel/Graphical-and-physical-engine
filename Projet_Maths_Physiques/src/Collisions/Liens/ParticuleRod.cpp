#include "Collisions/Liens/ParticuleRod.h"

unsigned int ParticuleRod::addContact(ParticuleContact* contact, unsigned int limit) {
	float current_length = currentLength();
	if (current_length = length) { //Longueur du bâton : on ne fait rien
		return 0;
	}

	//On ajoute les particules au contact

	contact->particules[0] = particules[0];
	contact->particules[1] = particules[1];

	//On calcule la normale

	Vecteur3D normal = particules[0]->getPos() - particules[1]->getPos();
	normal.normalized();

	if (current_length > length) { //Cas longueur plus élevée
		contact->contactNormal = normal;
		contact->penetration = current_length - length;
	}
	else { //Cas longueur plus courte
		contact->contactNormal = -1 * normal;
		contact->penetration = length - current_length;
	}

	//La restitution est toujours nulle

	contact->restitution = 0;

	return 1;
}