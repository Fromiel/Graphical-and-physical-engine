#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "Collider.h"

class SphereCollider : public Collider
{
	private:

	public:
		float radius;

		SphereCollider(Entity entity, float r = 1.0f, Vector3D position = Vector3D(), Vector3D orientation = Vector3D(), Rigidbody* rigidbody = NULL);

		float getMaxSize() const override { return radius; }
};

#endif