#include "Collisions/ParticuleContactResolver.h"
#include <algorithm>
#include <map>

void ParticuleContactResolver::resolveContacts(std::vector<ParticuleContact> contactArray, unsigned int numContact, float duration) {

	int it = 0;
	bool resolved = false;

	while (it < iteration && !resolved) {
		it++;

		//Calculer vélocités relatives de chaque contact
		std::map<ParticuleContact, float> velocitesRelative;
		for (ParticuleContact &pc : contactArray) {
			velocitesRelative.insert(std::make_pair(pc, pc.calculateSeparatingVelocity())); //vélocité relative ?
		}

		//Conserver la plus petite valeur (si cette valeur est > 0 => resolved = true)

		std::pair<ParticuleContact, float> minValue = minimum(velocitesRelative);
		
		float minVelocite = minValue.second;
		if (minVelocite > 0) resolved = true;
		
		minValue.first.resolve(0);

		
	}
}


std::pair<ParticuleContact, float> ParticuleContactResolver::minimum(std::map<ParticuleContact, float> map) {
	float min = INFINITY;
	ParticuleContact minPart;
	for (auto el : map) {
		if (el.second < min) {
			min = el.second;
			minPart = el.first;
		}
	}
	return std::make_pair(minPart, min);
}