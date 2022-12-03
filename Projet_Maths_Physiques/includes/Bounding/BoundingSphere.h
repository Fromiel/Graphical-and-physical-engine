#pragma once
#ifndef BOUNDING_SPHERE_H
#define BOUNDING_SPHERE_H

#include "Bounding.h"

class BoundingSphere : public Bounding {
public:
	//Constructeur par valeurs
	BoundingSphere(const Vecteur3D& cent, float r) : Bounding(cent), radius(r) {};

	//Constructeur englobant 2 sphères
	BoundingSphere(const BoundingSphere&, const BoundingSphere&);

	//Overlaps
	bool overlaps(const BoundingSphere* other) const;

	//Size
	float getSize() const override;

	float getRadius() const { return radius; }
protected:
	float radius;
};

#endif