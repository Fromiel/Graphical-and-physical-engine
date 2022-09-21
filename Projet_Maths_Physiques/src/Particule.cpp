#include "Particule.h"
#include <ctime>

Particule::Particule(Vecteur3D pos_initiale, Vecteur3D v_initiale, double r, double m) {
	position = pos_initiale;
	velocity = v_initiale;
	acceleration = 0;
	rayon = r;
	InverseMasse = m;
}

Particule::Particule(const Particule &p) {
	position = p.getPos();
	velocity = p.getVelocity();
	acceleration = p.getAcc();
	rayon = p.getRayon();
	InverseMasse = p.getInverseMasse();
}

void Particule::setPos(const Vecteur3D pos) {
	position = pos;
}

void Particule::setVelocity(const Vecteur3D s) {
	velocity = s;
}

void Particule::setAcceleration(const Vecteur3D a) {
	acceleration = a;
}

void Particule::update() {
	double h = time.h / ctime; 
	updateVelocity(h);
	updatePosition(h);
}

void Particule::updatePosition(double frameRate) {
	position = position + (frameRate * velocity);
}

void Particule::updateVelocity(double frameRate) {
	velocity = (pow(d,frameRate)) * velocity + (frameRate * acceleration);
}

