#include "Collisions/ParticuleLink.h"

ParticuleLink::currentLength() const {
	return distance(particules[0], particules[1]); //Not sure if current distance is intended or initial distance
}