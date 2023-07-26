#pragma once
#ifndef FORCE_GENERATOR_H
#define FORCE_GENERATOR_H

#include "Components/Rigidbody.h"

class ForceGenerator {
public:
	virtual void UpdateForce(Rigidbody*) = 0;
};

#endif