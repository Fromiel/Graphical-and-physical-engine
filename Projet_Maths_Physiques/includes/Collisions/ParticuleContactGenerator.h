#pragma once
#ifndef PARTICULE_CONTACT_GENERATOR_H
#define PARTICULE_CONTACT_GENERATOR_H

#include "ParticuleContact.h"

/// <summary>
/// Classe virtuelle pure permettant la génération de contacts entre particules
/// </summary>
class ParticuleContactGenerator {
public:
	virtual unsigned int addContact(ParticuleContact* contact, unsigned int limit) const = 0;
};

#endif