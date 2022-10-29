#include "Collisions/Liens/ParticuleCable.h"

unsigned int ParticuleCable::addContact(ParticuleContact* contact, unsigned int limit) const {
	if (currentLength() < maxLength) return 0; //On ne fait rien tant que le câble n'est pas tendu

	//On ajoute les particules au contact

	contact->particules[0] = particules[0];
	contact->particules[1] = particules[1];

	//On calcule la normale

	Vecteur3D normal = particules[0]->getPos() - particules[1]->getPos();
	normal.normalized();
	contact->contactNormal = normal;

	//On ajoute penetration et restitution

	contact->penetration = currentLength() - maxLength;
	contact->restitution = restitution;

	return 1;
	
}