#pragma once
#ifndef PARTICULE_CONTACT_H
#define PARTICULE_CONTACT_H

#include "Components/Particule.h"

class ParticuleContact {
public:
	~ParticuleContact();

	//Les 2 particules en contact
	Particule* particules[2];

	//Varie de 0 à 1 (= e), donne l'élasticité de la collision
	float restitution;

	//Distance de pénétration
	float penetration;

	//normale du contact
	Vector3D contactNormal;

	//Résolveur de la vélocité et interpénétration
	//NOTE : Implémentation des résolutions différente du livre (plus proche du cours ?); possibilité de changer en cas de dysfonctionnement
	void resolve(float duration);

	//Renvoie la vélocité de séparation des particules
	float calculateSeparatingVelocity() const;

	//Clear les valeurs
	void clear();

private:
	//Gère les impulsions de la collision
	void resolveVelocity(float duration);

	//Gère l'interpénétration de la collision
	void resolveInterpenetration();

	//Renvoie la valeur de k
	float calculateK(float duration) const;
};

//Opérateurs -> nécessaire à la compilation
bool operator<(const ParticuleContact&, const ParticuleContact&);

#endif