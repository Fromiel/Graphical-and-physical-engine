#include "Particule.h"


Particule::Particule(Vecteur3D pos, Vecteur3D s, Vecteur3D a, float r, float m) {
	position = pos;
	velocity = s;
	acceleration = a;
	rayon = r;
	InverseMasse = m;
}

Particule::Particule(const Particule &p) {
	position = p.getPos();
	velocity = p.getSpeed();
	acceleration = p.getAcc();
	rayon = p.getRayon();
	InverseMasse = p.getInverseMasse();
}

void Particule::setPos(const Vecteur3D pos) {
	position = pos;
}

void Particule::setSpeed(const Vecteur3D s) {
	velocity = s;
}

void Particule::setAcceleration(const Vecteur3D a) {
	acceleration = a;
}

