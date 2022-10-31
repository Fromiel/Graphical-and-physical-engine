#pragma once
#ifndef WALL_CONTACT_GENERATOR_H
#define WALL_CONTACT_GENERATOR_H

#include "ParticuleContactGenerator.h"

class WallContactGenerator : public ParticuleContactGenerator {
public:
	Vecteur3D bottom_left_corner;
	Vecteur3D up_right_corner;

	unsigned int addContact(ParticuleContact* contact, unsigned int limit) const;
};

#endif