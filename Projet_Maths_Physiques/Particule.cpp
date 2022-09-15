#include "Particule.h"

Particule::Particule(Vecteur3D pos, Vecteur3D s, Vecteur3D a, float r, float m) {
	position = Vecteur3D(pos);
	velocity = Vecteur3D(s);
	acceleration = Vecteur3D(a);
	rayon = r;
	InverseMasse = m;
}

Particule::Particule(const Particule& p) {
	position = Vecteur3D(p.getPos());
	velocity = Vecteur3D(p.getSpeed());
	acceleration = Vecteur3D(p.getAcc());
	rayon = p.getRayon();
	InverseMasse = p.getInverseMasse();
}

void Particule::setPos(const Vecteur3D pos) {
	position = Vecteur3D(pos);
}

void Particule::setSpeed(const Vecteur3D s) {
	velocity = Vecteur3D(s);
}

void Particule::setAcceleration(const Vecteur3D a) {
	acceleration = Vecteur3D(a);
}