#pragma once
#ifndef NAIVE_PARTICULE_CONTACT_GENERATOR_H
#define NAIVE_PARTICULE_CONTACT_GENERATOR_H

#include "ParticuleContactGenerator.h"
#include <vector>

class NaiveParticuleContactGenerator : public ParticuleContactGenerator {
public:
	NaiveParticuleContactGenerator(float r) : radius(r) {}
	//Rayon des particules
	float radius;

	//Particules qui collisionnent
	std::vector<Particule*> particules;

	//On itère sur chaque paire de particules pour vérifier la pénétration
	unsigned int addContact(ParticuleContact* contact, unsigned int limit) const;
};

#endif // !NAIVE_PARTICULE_CONTACT_GENERATOR_H
