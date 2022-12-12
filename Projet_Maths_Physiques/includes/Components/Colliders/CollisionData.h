#ifndef COLLISIONDATA_H
#define COLLISIONDATA_H

struct CollisionData
{
	//Normale au contact
	Vecteur3D normalContact;
	//Point du contact dans les coordonnées du monde
	Vecteur3D ptContact;
	//Penetration
	float penetration;
	//Rigidbody *rb1;
	//Rigidbody *rb2;
	//float coeff_restitution = 1;
	//float friction = 1;
};


#endif