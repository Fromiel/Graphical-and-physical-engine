#include "Components/Particule.h"

double Particule::g = 9.81;
double Particule::d = 0.7;
double Particule::sol = 0.0;

Particule::Particule(Vecteur3D pos_initiale, Vecteur3D v_initiale, double r, double m) {
	position = pos_initiale;
	velocity = v_initiale;
	//acceleration = Vecteur3D(0,-g,0);
	acceleration = Vecteur3D(0, 0, 0);
	rayon = r;
	InverseMasse = m;
	clearAccum();
	
}

Particule::Particule(const Particule &p) {
	position = p.getPos();
	velocity = p.getVelocity();
	acceleration = p.getAcc();
	rayon = p.getRayon();
	InverseMasse = p.getInverseMasse();
	clearAccum();
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

void Particule::update(double h) {
	std::cout << position << std::endl;
	//if (position.get_y() >= sol) {

		acceleration = AccumForce * InverseMasse; //Somme des forces (rpz par AccumForce) = m*acceleration
		std::cout << "Update with h = " << h << std::endl; //FOR DEBUG
		std::cout << "Particule at position : " << position << std::endl; //FOR DEBUG
		updateVelocity(h);
		updatePosition(h);
	//}
}

void Particule::updatePosition(double frameRate) {
	position = position +  (frameRate * velocity);
}

void Particule::updateVelocity(double frameRate) {
	std::cout << "Particule velocity is " << velocity.norm() << std::endl; //FOR DEBUG
	velocity = pow(d, frameRate) * velocity + frameRate * acceleration;
}

void Particule::addForce(const Vecteur3D& Force) {
	AccumForce = AccumForce + Force;
}

void Particule::clearAccum() {
	AccumForce = Vecteur3D(0, 0, 0);
}