#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "Collider.h"

class SphereCollider : public Collider
{
	private:

	public:
		float radius;

		SphereCollider(Entity entity, float r = 1.0f, Vecteur3D position = Vecteur3D(), Vecteur3D orientation = Vecteur3D(), Rigidbody* rigidbody = NULL);
};

#endif