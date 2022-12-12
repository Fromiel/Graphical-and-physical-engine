#ifndef PLANECOLLIDER_H
#define PLANECOLLIDER_H

#include "Collider.h"

class PlaneCollider : public Collider
{
	private:

	public:
		Vecteur3D normal;
		float offset;

		PlaneCollider(Entity entity, float offs = 0.0f, Vecteur3D n = Vecteur3D(0, 1, 0), Vecteur3D position = Vecteur3D(), Vecteur3D orientation = Vecteur3D(), Rigidbody* rigidbody = NULL);
};

#endif