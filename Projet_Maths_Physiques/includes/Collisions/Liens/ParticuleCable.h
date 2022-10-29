#pragma once
#ifndef PARTICULE_CABLE_H
#define PARTICULE_CABLE_H

#include "../ParticuleLink.h"

class ParticuleCable : public ParticuleLink {
public:
	// On g�n�re un contact seulement si distance(p1,p2) > maxLength
	float maxLength;

	//Coefficient de restitution
	float restitution;

	//Remplie le ParticuleContact avec les informations des particules et du g�n�rateur
	unsigned int addContact(ParticuleContact* contact, unsigned int limit) const;
};

#endif