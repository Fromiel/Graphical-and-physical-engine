#include "Collisions/ParticuleContactResolver.h"
#include <algorithm>
#include <map>

void ParticuleContactResolver::resolveContacts(std::vector<ParticuleContact*> contactArray, unsigned int numContact, float duration) {

	if (contactArray.size() == 0) return;

	int it = 0;
	bool resolved = false;

	std::cout << "** RESOLVER DEBUG **" << std::endl;

	while (it < iteration && !resolved) {
		it++;

		std::cout << "While loop with it = " << it << std::endl;

		//Calculer vélocités relatives de chaque contact
		std::map<ParticuleContact*, float> velocitesRelative;
		for (ParticuleContact* pc : contactArray) {
			std::cout << "Adding contact (penetration) " << pc->penetration << std::endl;
			std::pair<ParticuleContact*, float> debug_value = std::make_pair(pc, pc->calculateSeparatingVelocity());
			std::cout << "To Add to Map : " << debug_value.first->penetration << " ; vel = " << debug_value.second << std::endl;
			velocitesRelative.insert(std::make_pair(pc, pc->calculateSeparatingVelocity())); //vélocité relative ?
			std::cout << "Added" << std::endl;
		}

		std::cout << "Map is setup with " << velocitesRelative.size() << " elements" << std::endl;

		//Conserver la plus petite valeur (si cette valeur est > 0 => resolved = true)

		std::pair<ParticuleContact*, float> minValue = minimum(velocitesRelative);

		float minVelocite = minValue.second;
		if (minVelocite >= 0) resolved = true;

		std::cout << "Min value is " << minVelocite << std::endl;
		
		minValue.first->resolve(0);

		
	}

	std::cout << "***********" << std::endl;
}


std::pair<ParticuleContact*, float> ParticuleContactResolver::minimum(std::map<ParticuleContact*, float> map) {
	float min = INFINITY;
	ParticuleContact* minPart;
	for (auto el : map) {
		if (el.second < min) {
			min = el.second;
			minPart = el.first;
		}
	}
	return std::make_pair(minPart, min);
}

void ParticuleContactResolver::SetIterations(unsigned int value) {
	iteration = value;
}