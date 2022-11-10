#include "Forces/SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator() {
	m_bodyAnchor = Vecteur3D();
	m_otherBodyAnchor = Vecteur3D();
	m_k = 0;
	m_rest_length = 0;
}

SpringForceGenerator::SpringForceGenerator(const Vecteur3D& bodyAnchor, Rigidbody* otherRigidbody, const Vecteur3D otherAnchor, float mk, float restlength) {
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
	//On récupère nos points de connection dans le repère world
	Vecteur3D connection_point_world = rigidbody->convertToWorld(m_bodyAnchor);
	Vecteur3D other_point_world = m_otherRigidbody->convertToWorld(m_otherBodyAnchor);

	//On calcule la force
	Vecteur3D force = connection_point_world - other_point_world;

	//On calcule la norme de la force
	float forceValue = force.norm();
	forceValue = abs(forceValue - m_rest_length); //Différence avec notre longueur au repos
	forceValue = forceValue * m_k; //Multipliée par le coefficient k (constante du ressort)

	//On applique finalement la force
	force.normalized();
	force = force *  (-forceValue);
	rigidbody->addForceAtPoint(force, connection_point_world);
}