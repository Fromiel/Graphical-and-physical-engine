#pragma once
#ifndef BOUNDING_H
#define BOUNDING_H

#include "Maths/Vector3D.h"

class Bounding {
public:
	//Constructeur par défaut
	Bounding() = default;

	//Constructeur par valeur
	Bounding(const Vector3D& c) :center(c) {};

	//Getter du centre
	Vector3D getCenter() const { return center; }

	//Renvoie la taille du bounding
	float virtual getSize() const = 0;

	//Indique si on se superpose à un autre Bounding
	//bool virtual overlaps(const Bounding* other) const = 0; //DEPRECIATED BECAUSE OF CAST COMPILE ERRORS
protected:
	Vector3D center;
};

#endif