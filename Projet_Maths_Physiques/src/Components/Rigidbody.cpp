#include "Components/Rigidbody.h"

Rigidbody::Rigidbody(Entity entityparent, float angularDamping, float invmasse, float linearDamping) : entity(entityparent) {
	m_angularDamping = angularDamping;
	m_linearDamping = linearDamping;
	inverseMasse = invmasse;
	clearAccumulator();
}

Rigidbody::Rigidbody(const Rigidbody& rb) {
	m_angularDamping = rb.getAngularDamping();
	m_forceAccum = rb.getForceAccum();
	m_torqueAccum = rb.getTorqueAccum();
}

Vecteur3D Rigidbody::getPos() const
{
	return Coordinator::getInstance()->getComponent<Transform>(entity).getPosition();
}

Quaternion Rigidbody::getOrientation() const 
{
	return Coordinator::getInstance()->getComponent<Transform>(entity).getOrientation();
}

Matrix4D Rigidbody::getModelMatrix() const
{
	return Coordinator::getInstance()->getComponent<Transform>(entity).getModelMatrix();
}


void Rigidbody::setVelocity(const Vecteur3D Velocity) {
	velocity = Velocity
}

void Rigidbody::setRotation(const Vecteur3D Rotation)
{
	rotation = Rotation;
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
	// On normalise l'orientation

	Quaternion recup = getOrientation();
	recup.normalize();
	Coordinator::getInstance()->getComponent<Transform>(entity).setOrientation(recup);

	// TODO : Calculer la nouvelle valeur de I^(-1)
}

void Rigidbody::Integrate(float duration) {

}

// TODO : Implémenter cette méthode pour de vrai
Vecteur3D Ridigbody::convertToWorld(const Vecteur3D& localPoint)
{
	return Vector3D(0, 0, 0);
}

