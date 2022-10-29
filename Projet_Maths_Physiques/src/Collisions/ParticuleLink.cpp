#include "Collisions/ParticuleLink.h"

float ParticuleLink::currentLength() const {
	//return 0;
	return distance(particules[0]->getPos(), particules[1]->getPos()); //Not sure if current distance is intended or initial distance
}