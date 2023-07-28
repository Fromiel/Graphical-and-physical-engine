#pragma once
#ifndef WALL_CONTACT_GENERATOR_H
#define WALL_CONTACT_GENERATOR_H

#include "ParticuleContactGenerator.h"

class WallContactGenerator : public ParticuleContactGenerator {
public:
	Vector3D center;
	Vector3D normale;
	Particule* particule;
	float thickness;

	WallContactGenerator(Particule*, Vector3D, Vector3D, float);
	~WallContactGenerator();

	unsigned int addContact(ParticuleContact* contact, unsigned int limit) const;
};

#endif