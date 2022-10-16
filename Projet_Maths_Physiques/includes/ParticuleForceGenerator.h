#pragma once
#ifndef PARTICULE_FORCE_GENERATOR_H
#define PARTICULE_FORCE_GENERATOR_H

#include "Particule.h"

class ParticuleForceGenerator {
public:
	virtual void updateForce(Particule*, float) = 0;
};

#endif