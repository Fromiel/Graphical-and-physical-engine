#ifndef COLLIDER_H
#define COLLIDER_H

#include "Components/Rigidbody.h"

class Collider
{
	private:
		Rigidbody *rigidbody_;
		Matrix34 offset_;

	public:
		//Collider(Entity entity, Matrix34 offset);

};

#endif