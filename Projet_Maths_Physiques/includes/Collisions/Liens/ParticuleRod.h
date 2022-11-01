#pragma once
#ifndef PARTICULE_ROD_H
#define PARTICULE_ROD_H

#include "../ParticuleLink.h"

class ParticuleRod : public ParticuleLink {
public:
	ParticuleRod(float, Particule*, Particule*);

	//Longueur de la tige : la distance entre les 2 particules est constante
	float length;

	// Remplie le ParticuleContact avec les informations des particules et le générateur
	// Note : Le contact est différent en fonction de si on est inférieur ou supérieur à la longueur de la tige
	unsigned int addContact(ParticuleContact* contact, unsigned int limit) const;
};

#endif // !PARTICULE_ROD_H
