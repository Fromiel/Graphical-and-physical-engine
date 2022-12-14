#ifndef PLANECOLLIDER_H
#define PLANECOLLIDER_H

#include "Collider.h"

class PlaneCollider : public Collider
{
	private:

	public:
		Vecteur3D normal;
		float halfSizeX;
		float halfSizeY;

		PlaneCollider(Entity entity, float halfSX = 1.0f, float halfSY = 1.0f, Vecteur3D n = Vecteur3D(0, 1, 0), Vecteur3D position = Vecteur3D(), Vecteur3D orientation = Vecteur3D(), Rigidbody* rigidbody = NULL);

		float getMaxSize() const override;
};

#endif