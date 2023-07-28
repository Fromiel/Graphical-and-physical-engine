#include "Forces/GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(float g) {
	gravity = Vector3D(0, g, 0);
}

void GravityForceGenerator::UpdateForce(Rigidbody* rigidbody) {
	float invmasse = rigidbody->getinverseMasse();
	if (invmasse == 0) std::cout << "Warning : 1/m = 0 => m will be INFINITY" << std::endl; //Useful in case of bugs regarding this specific behaviour
	float masse = (invmasse == 0) ? INFINITY : (1 / invmasse);

	rigidbody->addForce(masse * gravity);
}