#pragma once
#ifndef PARTICULE_CONTACT_H
#define PARTICULE_CONTACT_H

#include "Particule.h"

class ParticuleContact {
public:
	//Les 2 particules en contact
	Particule* particules[2];

	//Varie de 0 � 1 (= e), donne l'�lasticit� de la collision
	float restitution;

	//Distance de p�n�tration
	float penetration;

	//normale du contact
	Vecteur3D contactNormal;

	//R�solveur de la v�locit� et interp�n�tration
	void resolve(float duration);

	//Renvoie la v�locit� de s�paration des particules
	void calculateSeparatingVelocity();

private:
	//G�re les impulsions de la collision
	void resolveVelocity();

	//G�re l'interp�n�tration de la collision
	void resolveInterpenetration();
};

#endif