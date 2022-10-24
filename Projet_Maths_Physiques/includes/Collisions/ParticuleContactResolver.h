#pragma once
#ifndef PARTICULE_CONTACT_RESOLVER_H
#define PARTICULE_CONTACT_RESOLVER_H

#include "ParticuleContact.h"

class ParticuleContactResolver {
protected:
	//nombre d'it�ration max
	unsigned int iteration;
public:
	/// <summary>
	/// Prend un tableau de contact, it�re sur chacun � partir de leur v�locit� de s�paration et arr�te quand tout � �t� r�solu ou qu'on d�passe le nombre max d'it�rations 
	/// </summary>
	/// <param name="contactArray">Les contacts entre particules</param>
	/// <param name="numContact">Le nombre de contacts</param>
	/// <param name="duration">La dur�e</param>
	void resolveContacts(ParticuleContact* contactArray, unsigned int numContact, float duration);
};

#endif