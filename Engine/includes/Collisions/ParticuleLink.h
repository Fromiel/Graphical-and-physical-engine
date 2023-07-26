#pragma once
#ifndef PARTICULE_LINK_H
#define PARTICULE_LINK_H

#include "ParticuleContactGenerator.h"

class ParticuleLink : ParticuleContactGenerator {
public:
	// Particules liées
	Particule* particules[2];

	//Longueur de la connexion
	float currentLength() const;

	//Ajoute les contacts
	unsigned int addContact(ParticuleContact* contact, unsigned int limit) const = 0;

};

#endif // !PARTICULE_LINK_H
