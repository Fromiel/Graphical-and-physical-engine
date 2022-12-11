#ifndef COLLISIONDATA_H
#define COLLISIONDATA_H

struct CollisionData
{
	Vecteur3D normalContact;
	Vecteur3D ptContact;
	float penetration;
	//Rigidbody *rb1;
	//Rigidbody *rb2;
	//float coeff_restitution = 1;
	//float friction = 1;
};


#endif