#pragma once
#ifndef WALL_CONTACT_GENERATOR_H
#define WALL_CONTACT_GENERATOR_H

#include "ParticuleContactGenerator.h"

class WallContactGenerator : public ParticuleContactGenerator {
public:
	Vecteur3D center;
	Vecteur3D normale;
	Particule* particule;
	float thickness;

	WallContactGenerator(Particule*, Vecteur3D, Vecteur3D, float);
	~WallContactGenerator();

	unsigned int addContact(ParticuleContact* contact, unsigned int limit) const;
};

#endif