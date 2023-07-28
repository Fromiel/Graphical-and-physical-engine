#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "Collider.h"

class BoxCollider : public Collider
{
	private:

	public:
		Vector3D halfsize;
		BoxCollider(Entity entity, Vector3D halfS = Vector3D(1, 1, 1), Vector3D position = Vector3D(), Vector3D orientation = Vector3D(), Rigidbody* rigidbody = NULL);

		float getMaxSize() const override;
};

#endif