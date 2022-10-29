#pragma once
#ifndef PARTICULE_CONTACT_RESOLVER_H
#define PARTICULE_CONTACT_RESOLVER_H

#include <vector>
#include <unordered_map>
#include "ParticuleContact.h"

class ParticuleContactResolver {
protected:
	//nombre d'itération max
	unsigned int iteration;

	//ParticuleContact ayant le float minimum dans une map
	std::pair<ParticuleContact, float> minimum(std::unordered_map<ParticuleContact, float>);
public:
	/// <summary>
	/// Prend un tableau de contact, itère sur chacun à partir de leur vélocité de séparation et arrête quand tout a été résolu ou qu'on dépasse le nombre max d'itérations 
	/// </summary>
	/// <param name="contactArray">Les contacts entre particules</param>
	/// <param name="numContact">Le nombre de contacts</param>
	/// <param name="duration">La durée</param>
	void resolveContacts(std::vector<ParticuleContact> contactArray, unsigned int numContact, float duration);
};

#endif