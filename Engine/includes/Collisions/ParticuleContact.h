#pragma once
#ifndef PARTICULE_CONTACT_H
#define PARTICULE_CONTACT_H

#include "Components/Particule.h"

class ParticuleContact {
public:
	~ParticuleContact();

	//Les 2 particules en contact
	Particule* particules[2];

	//Varie de 0 � 1 (= e), donne l'�lasticit� de la collision
	float restitution;

	//Distance de p�n�tration
	float penetration;

	//normale du contact
	Vector3D contactNormal;

	//R�solveur de la v�locit� et interp�n�tration
	//NOTE : Impl�mentation des r�solutions diff�rente du livre (plus proche du cours ?); possibilit� de changer en cas de dysfonctionnement
	void resolve(float duration);

	//Renvoie la v�locit� de s�paration des particules
	float calculateSeparatingVelocity() const;

	//Clear les valeurs
	void clear();

private:
	//G�re les impulsions de la collision
	void resolveVelocity(float duration);

	//G�re l'interp�n�tration de la collision
	void resolveInterpenetration();

	//Renvoie la valeur de k
	float calculateK(float duration) const;
};

//Op�rateurs -> n�cessaire � la compilation
bool operator<(const ParticuleContact&, const ParticuleContact&);

#endif