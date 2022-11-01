#include "Collisions/Liens/ParticuleRod.h"

ParticuleRod::ParticuleRod(float l, Particule* p1, Particule* p2) {
	length = l;
	particules[0] = p1;
	particules[1] = p2;
}

unsigned int ParticuleRod::addContact(ParticuleContact* contact, unsigned int limit) const {
	float current_length = currentLength();
	if (current_length == length) { //Longueur du bâton : on ne fait rien
		return 0;
	}

	//DEBUG

	std::cout << "Rod.addContact : current_length is " << current_length << " and Rod length is " << length << std::endl;
	if (particules[0]) std::cout << "Particule 0 is at " << particules[0]->getPos() << std::endl;
	if (particules[1]) std::cout << "Particule 1 is at " << particules[1]->getPos() << std::endl;

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

	std::cout << "Penetration is " << contact->penetration << std::endl;
	std::cout << "Normale is " << contact->contactNormal << std::endl;

	return 1;
}