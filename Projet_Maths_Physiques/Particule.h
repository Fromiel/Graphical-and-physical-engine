#pragma once
#ifndef PARTICULE_H
#define PARTICULE_H

#include "Vecteur3D.h"

class Particule {
public:
	//Constructeurs//

	Particule(Vecteur3D pos, Vecteur3D vel, Vecteur3D acc, float r, float m);
	Particule(const Particule &p);

	//Getters//

	/**
	* Getter pour l'attribut InverseMasse de la classe
	*/
	float getInverseMasse() const { return InverseMasse; }

	/**
	* Getter pour l'attribut rayon de la classe
	*/
	float getRayon() const { return rayon; }

	/**
	* Getter pour l'attribut position de la classe
	*/
	Vecteur3D getPos() const { return position; }

	/**
	* Getter pour l'attribut velocity de la classe
	*/
	Vecteur3D getSpeed() const { return velocity; }

	/**
	* Getter pour l'attribut acceleration de la classe
	*/
	Vecteur3D getAcc() const { return acceleration; }
	
	//Setters//
	
	/**
	* Setter pour l'attribut position de la classe
	*/
	void setPos(const Vecteur3D);

	/**
	* Setter pour l'attribut velocity de la classe
	*/
	void setSpeed(const Vecteur3D);

	/**
	* Setter pour l'attribut acceleration de la classe
	*/
	void setAcceleration(const Vecteur3D);

private:
	Vecteur3D position;
	Vecteur3D velocity;
	Vecteur3D acceleration;
	float rayon;
	float InverseMasse;

};

#endif
