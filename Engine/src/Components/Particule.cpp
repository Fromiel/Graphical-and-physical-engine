#include "Components/Particule.h"
#include "Components/Transform.h"
//#include "Forces/ParticuleGravity.h"
//#include "Forces/ParticuleRessortPtFixe.h"
//#include "Forces/ParticuleRessortPtPt.h"
//#include "Forces/ParticuleBungee.h"



float Particule::g = 9.81f;
float Particule::d = 0.7f;
float Particule::sol = 0.0f;

Particule::Particule(Entity entityParent, Vector3D v_initiale, float r, float m) : entity(entityParent) {
	velocity = v_initiale;
	//acceleration = Vecteur3D(0,-g,0);
	acceleration = Vector3D(0.0f, 0.0f, 0.0f);
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

Vector3D Particule::getPos() const
{ 
	return Coordinator::getInstance()->getComponent<Transform>(entity).getPosition();
}

void Particule::setPos(const Vector3D pos) {
	Coordinator* coordinator = Coordinator::getInstance();
	coordinator->getComponent<Transform>(entity).setPosition(pos);
}

void Particule::setVelocity(const Vector3D s) {
	velocity = s;
}

void Particule::setAcceleration(const Vector3D a) {
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
	Vector3D pos = coordinator->getComponent<Transform>(entity).getPosition();
	coordinator->getComponent<Transform>(entity).setPosition(pos + (frameRate * velocity));
}

void Particule::updateVelocity(float frameRate) {
	//std::cout << "Particule velocity is " << velocity.norm() << std::endl; //FOR DEBUG
	velocity = pow(d, frameRate) * velocity + frameRate * acceleration;
}

void Particule::addForce(const Vector3D& Force) {
	AccumForce = AccumForce + Force;
}

void Particule::clearAccum() {
	AccumForce = Vector3D(0, 0, 0);
}