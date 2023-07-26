#ifndef COLLISIONDATA_H
#define COLLISIONDATA_H

#include <iostream>

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

	friend std::ostream& operator<<(std::ostream& os, const CollisionData c)
	{
		os << "Normal : " << c.normalContact << std::endl;
		os << "Point de contact : " << c.ptContact << std::endl;
		os << "Penetration : " << c.penetration << std::endl;
		return os;
	}

};



#endif