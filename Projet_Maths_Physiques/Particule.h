#pragma once
#ifndef PARTICULE_H
#define PARTICULE_H

#include "Vecteur3D.h"

class Particule {
public:
	//Constructeurs
	Particule(Vecteur3D pos, Vecteur3D vel, Vecteur3D acc, float r, float m);
	Particule(const Particule &p);
	//Getters
	float getInverseMasse() const { return InverseMasse; }
	float getRayon() const { return rayon; }
	Vecteur3D getPos() const { return position; }
	Vecteur3D getSpeed() const { return velocity; }
	Vecteur3D getAcc() const { return acceleration; }
	//Setters
	void setPos(const Vecteur3D);
	void setSpeed(const Vecteur3D);
	void setAcceleration(const Vecteur3D);

private:
	Vecteur3D position;
	Vecteur3D velocity;
	Vecteur3D acceleration;
	float rayon;
	float InverseMasse;

};

#endif
