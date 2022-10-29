#include "Collisions/ParticuleContactResolver.h"
#include <algorithm>
#include <unordered_map>

/*ParticuleContactResolver::resolveContacts(std::vector<ParticuleContact> contactArray, unsigned int numContact, float duration) {

	int it = 0;
	bool resolved = false;

	while (it < iteration && !resolved) {
		it++;

		//Calculer vélocités relatives de chaque contact
		std::unordered_map<ParticuleContact, float> velocitesRelative;
		for (ParticuleContact pc : contactArray) {
			velocitesRelative.push_back(std::make_pair<ParticuleContact, float>(pc, pc.calculateSeparatingVelocity()); //vélocité relative ?
		}

		//Conserver la plus petite valeur (si cette valeur est > 0 => resolved = true)

		std::pair<ParticuleContact, float> minValue = minimum(velocitesRelative);
		
		float minVelocite = minValue.second;
		if (minVelocite > 0) resolved = true;
		
		minValue.first.resolve();

		
	}
}

std::pair<ParticuleContact, float> ParticuleContactResolver::minimum(std::unordered_map<ParticuleContact, float> map) {
	float min = INFINITY;
	ParticuleContact minPart;
	for (auto el : map) {
		if (el.second < min) {
			min = el.second;
			minPart = el.first;
		}
	}
	return std::make_pair<ParticuleContact, float>(minPart, min);
}*/