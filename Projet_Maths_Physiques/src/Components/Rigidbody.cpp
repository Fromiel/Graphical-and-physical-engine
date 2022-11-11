#include "Components/Rigidbody.h"

Rigidbody::Rigidbody(Entity entityparent, float angularDamping, float invmasse, float linearDamping) : entity(entityparent) {
	m_angularDamping = angularDamping;
	m_linearDamping = linearDamping;
	inverseMasse = invmasse;
	accel_lineaire = Vecteur3D(0, 0, 0);
	accel_rotation = Vecteur3D(0, 0, 0);
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
	velocity = Velocity;
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
	accel_lineaire = inverseMasse * m_forceAccum;
	// TODO : calculer l'accélération angulaire
	accel_rotation = 0;

	// Vitesse
	velocity = velocity + (accel_lineaire * duration);
	velocity = velocity * pow(m_linearDamping, duration);
	rotation = rotation + accel_rotation * duration;
	rotation = rotation * pow(m_angularDamping, duration);

	// Position 
	Vecteur3D pos_res = getPos();
	pos_res = pos_res + velocity * duration;
	Coordinator::getInstance()->getComponent<Transform>(entity).setPosition(pos_res);

	Quaternion ori = getOrientation();
	ori.updateByAngularVelocity(rotation, duration);
	Coordinator::getInstance()->getComponent<Transform>(entity).setOrientation(ori);

	CalculateDerivatedData();
	clearAccumulator();
}

// TODO : Implémenter cette méthode pour de vrai
Vecteur3D Rigidbody::convertToWorld(const Vecteur3D& localPoint)
{
	return Vecteur3D(0, 0, 0);
}

