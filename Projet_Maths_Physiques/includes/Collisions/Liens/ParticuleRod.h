#pragma once
#ifndef PARTICULE_ROD_H
#define PARTICULE_ROD_H

#include "../ParticuleLink.h"

class ParticuleRod : public ParticuleLink {
public:
	//Longueur de la tige : la distance entre les 2 particules est constante
	float length;

	// Remplie le ParticuleContact avec les informations des particules et le g�n�rateur
	// Note : Le contact est diff�rent en fonction de si on est inf�rieur ou sup�rieur � la longueur de la tige
	unsigned int addContact(ParticuleContact* contact, unsigned int limit);
};

#endif // !PARTICULE_ROD_H
