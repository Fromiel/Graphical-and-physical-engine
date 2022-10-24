#pragma once
#ifndef PARTICULE_CONTACT_RESOLVER_H
#define PARTICULE_CONTACT_RESOLVER_H

#include "ParticuleContact.h"

class ParticuleContactResolver {
protected:
	//nombre d'itération max
	unsigned int iteration;
public:
	/// <summary>
	/// Prend un tableau de contact, itère sur chacun à partir de leur vélocité de séparation et arrête quand tout à été résolu ou qu'on dépasse le nombre max d'itérations 
	/// </summary>
	/// <param name="contactArray">Les contacts entre particules</param>
	/// <param name="numContact">Le nombre de contacts</param>
	/// <param name="duration">La durée</param>
	void resolveContacts(ParticuleContact* contactArray, unsigned int numContact, float duration);
};

#endif