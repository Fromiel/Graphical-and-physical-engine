#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "Collider.h"

class BoxCollider : public Collider
{
	private:

	public:
		Vecteur3D halfsize;
		BoxCollider(Entity entity, Vecteur3D halfS = Vecteur3D(1, 1, 1), Vecteur3D position = Vecteur3D(), Vecteur3D orientation = Vecteur3D(), Rigidbody* rigidbody = NULL);
};

#endif