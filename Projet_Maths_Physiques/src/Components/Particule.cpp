#include "Components/Particule.h"

float Particule::g = 9.81f;
float Particule::d = 0.7f;
float Particule::sol = 0.0f;

Particule::Particule(Entity entityParent, Vecteur3D v_initiale, float r, float m) : entity(entityParent) {
	velocity = v_initiale;
	//acceleration = Vecteur3D(0,-g,0);
	acceleration = Vecteur3D(0.0f, 0.0f, 0.0f);
	rayon = r;
	InverseMasse = m;
	clearAccum();
	
}

Particule::Particule(const Particule &p) : entity(p.entity) {
	velocity = p.getVelocity();
	acceleration = p.getAcc();
	rayon = p.getRayon();
	InverseMasse = p.getInverseMasse();
	clearAccum();
}

Vecteur3D Particule::getPos() const
{ 
	return Coordinator::getInstance()->getComponent<Transform>(entity).getPosition();
}

void Particule::setPos(const Vecteur3D pos) {
	Coordinator* coordinator = Coordinator::getInstance();
	coordinator->getComponent<Transform>(entity).setPosition(pos);
}

void Particule::setVelocity(const Vecteur3D s) {
	velocity = s;
}

void Particule::setAcceleration(const Vecteur3D a) {
	acceleration = a;
}

void Particule::update(float h) {
	//std::cout << position << std::endl;
	//if (position.get_y() >= sol) {

		acceleration = AccumForce * InverseMasse; //Somme des forces (rpz par AccumForce) = m*acceleration
		//std::cout << "Update with h = " << h << std::endl; //FOR DEBUG
		//std::cout << "Particule at position : " << position << std::endl; //FOR DEBUG
		updateVelocity(h);
		updatePosition(h);
	//}
}

void Particule::updatePosition(float frameRate) {
	Coordinator* coordinator = Coordinator::getInstance();
	Vecteur3D pos = coordinator->getComponent<Transform>(entity).getPosition();
	coordinator->getComponent<Transform>(entity).setPosition(pos + (frameRate * velocity));
}

void Particule::updateVelocity(float frameRate) {
	//std::cout << "Particule velocity is " << velocity.norm() << std::endl; //FOR DEBUG
	velocity = pow(d, frameRate) * velocity + frameRate * acceleration;
}

void Particule::addForce(const Vecteur3D& Force) {
	AccumForce = AccumForce + Force;
}

void Particule::clearAccum() {
	AccumForce = Vecteur3D(0, 0, 0);
}