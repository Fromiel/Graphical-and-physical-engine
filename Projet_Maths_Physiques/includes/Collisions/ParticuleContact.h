#pragma once
#ifndef PARTICULE_CONTACT_H
#define PARTICULE_CONTACT_H

#include "Particule.h"

class ParticuleContact {
public:
	//Les 2 particules en contact
	Particule* particules[2];

	//Varie de 0 à 1 (= e), donne l'élasticité de la collision
	float restitution;

	//Distance de pénétration
	float penetration;

	//normale du contact
	Vecteur3D contactNormal;

	//Résolveur de la vélocité et interpénétration
	void resolve(float duration);

	//Renvoie la vélocité de séparation des particules
	void calculateSeparatingVelocity();

private:
	//Gère les impulsions de la collision
	void resolveVelocity();

	//Gère l'interpénétration de la collision
	void resolveInterpenetration();
};

#endif