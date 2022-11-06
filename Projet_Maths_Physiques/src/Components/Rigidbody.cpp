#include "Components/Rigidbody.h"

Rigidbody::Rigidbody(Entity entityparent, float angularDamping) : entity(entityparent) {
	m_angularDamping = angularDamping;
	m_forceAccum = Vecteur3D(0, 0, 0);
	m_torqueAccum = Vecteur3D(0, 0, 0);
}

Rigidbody::Rigidbody(const Rigidbody& rb) {
	m_angularDamping = rb.getAngularDamping();
	m_forceAccum = rb.getForceAccum();
	m_torqueAccum = rb.getTorqueAccum();
}

void Rigidbody::addForce(const Vecteur3D& force) {

}

void Rigidbody::addForceAtPoint(const Vecteur3D& force, const Vecteur3D& worldpoint) {

}

void Rigidbody::addForceAtBodyPoint(const Vecteur3D& force, const Vecteur3D& localpoint) {

}

void Rigidbody::clearAccumulator() {
	m_forceAccum = Vecteur3D(0, 0, 0);
	m_torqueAccum = Vecteur3D(0, 0, 0);
}

void Rigidbody::CalculateDerivatedData() {

}

void Rigidbody::Integrate(float duration) {

}

