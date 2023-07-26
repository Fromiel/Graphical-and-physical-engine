#include "Collisions/WallContactGenerator.h"

unsigned int WallContactGenerator::addContact(ParticuleContact* contact, unsigned int limit) const {
	float distance = (scalar_product(normale, particule->getPos() - center));

	if (abs(distance) > (thickness / 2)) return 0; //On est pas dans le mur : on quitte

	contact->particules[0] = particule;
	contact->contactNormal = normale;

	if ((distance) > 0) { //Si on est côté "entrée" on pousse dans un sens...
		contact->penetration = (thickness/2) - distance; //+/- to check 
	}
	else {
		contact->penetration = (thickness / 2) + distance; //... ou dans l'autre
	}

	contact->penetration = 0;
	return 1;

}

WallContactGenerator::WallContactGenerator(Particule* ptr, Vecteur3D cen = Vecteur3D(0,0,0), Vecteur3D nor = Vecteur3D(0,0,0), float thick = 0) {
	particule = ptr;
	center = cen;
	normale = nor;
	thickness = thick;
}

WallContactGenerator::~WallContactGenerator() {
	delete particule;
}