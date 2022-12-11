#ifndef PLANECOLLIDER_H
#define PLANECOLLIDER_H

#include "Collider.h"

class PlaneCollider : public Collider
{
	private:

	public:
		Vecteur3D normal;
		float offset;
};

#endif