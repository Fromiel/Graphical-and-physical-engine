#pragma once
#ifndef GRAVITY_FORCE_GENERATOR_H
#define GRAVITY_FORCE_GENERATOR_H

#include "ForceGenerator.h"

class GravityForceGenerator : public ForceGenerator {
private:
	Vecteur3D gravity;
public:
	//Constructeur(s)

	GravityForceGenerator(float g = -9.81);

	//Fonctions

	void UpdateForce(Rigidbody* rigidbody) override;
};

#endif