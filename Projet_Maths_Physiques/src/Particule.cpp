#include "Particule.h"

double Particule::g = 9.81;
double Particule::d = 0.7;

Particule::Particule(Vecteur3D pos_initiale, Vecteur3D v_initiale, double r, double m) {
	position = pos_initiale;
	velocity = v_initiale;
	acceleration = Vecteur3D(0,-g,0);
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

void Particule::update(double h) { 
	std::cout << "Update with h = " << h << std::endl;
	updateVelocity(h);
	updatePosition(h);
}

void Particule::updatePosition(double frameRate) {
	//std::cout << "vel * frameRate = " << velocity.scalar_multiplication(frameRate) << std::endl;
	//position = position + (velocity.scalar_multiplication(frameRate));
	position = position +  (frameRate * velocity);
}

void Particule::updateVelocity(double frameRate) {
	//std::cout << "pow(d,frameRate)) = " << (pow(d, frameRate))  << std::endl;
	//std::cout << "frameRate = " << frameRate << std::endl;
	//std::cout << "acceleration = " << acceleration << std::endl;
	//std::cout << "frameRate*acceleration = " << (frameRate*acceleration) << std::endl;
	//std::cout << "frameRate * acceleration = " << acceleration.scalar_multiplication(frameRate) << std::endl;
	//velocity =  velocity.scalar_multiplication((pow(d, frameRate))) + (acceleration.scalar_multiplication(frameRate));
	velocity = pow(d, frameRate) * velocity + frameRate * acceleration;
}

