#ifndef PLANECOLLIDER_H
#define PLANECOLLIDER_H

#include "Collider.h"

class PlaneCollider : public Collider
{
	private:


	public:
		float halfSizeX;
		float halfSizeZ;

		PlaneCollider(Entity entity, float halfSX = 1.0f, float halfSZ = 1.0f, Vector3D position = Vector3D(), Vector3D orientation = Vector3D(), Rigidbody* rigidbody = NULL);

		float getMaxSize() const override;
};

#endif