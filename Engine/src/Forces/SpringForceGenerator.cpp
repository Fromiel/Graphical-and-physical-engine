#include "Forces/SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator() {
	m_bodyAnchor = Vector3D();
	m_otherBodyAnchor = Vector3D();
	m_k = 0;
	m_rest_length = 0;
}

SpringForceGenerator::SpringForceGenerator(const Vector3D& bodyAnchor, Rigidbody* otherRigidbody, const Vector3D otherAnchor, float mk, float restlength) {
	m_bodyAnchor = bodyAnchor;
	m_otherRigidbody = otherRigidbody;
	m_otherBodyAnchor = otherAnchor;
	m_k = mk;
	m_rest_length = restlength;
}

SpringForceGenerator::~SpringForceGenerator() {
	delete m_otherRigidbody;
}

void SpringForceGenerator::UpdateForce(Rigidbody* rigidbody) {
	//On r�cup�re nos points de connection dans le rep�re world
	Vector3D connection_point_world = rigidbody->convertToWorld(m_bodyAnchor);
	Vector3D other_point_world = m_otherRigidbody->convertToWorld(m_otherBodyAnchor);

	//On calcule la force
	Vector3D force = connection_point_world - other_point_world;

	//On calcule la norme de la force
	float forceValue = force.norm();
	forceValue = (forceValue - m_rest_length); //Diff�rence avec notre longueur au repos
	forceValue = forceValue * m_k; //Multipli�e par le coefficient k (constante du ressort)

	//On applique finalement la force
	force.normalized();
	force = force *  (-forceValue);
	rigidbody->addForceAtPoint(force, connection_point_world);
}