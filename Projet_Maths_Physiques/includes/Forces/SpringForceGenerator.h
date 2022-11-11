#pragma once
#ifndef SPRING_FORCE_GENERATOR_H
#define SPRING_FORCE_GENERATOR_H

#include "ForceGenerator.h"

//ForceGenerator for Spring (= Ressorts)
class SpringForceGenerator : public ForceGenerator {
private:
	//Anchor point in local coordinate
	Vecteur3D m_bodyAnchor;

	//Other Rigidbody (?)
	Rigidbody* m_otherRigidbody = nullptr;

	//Other Anchor point in local coordinate
	Vecteur3D m_otherBodyAnchor;

	//Spring parameters
	float m_k;
	float m_rest_length;
public:
	//Constructeurs
	SpringForceGenerator();
	SpringForceGenerator(const Vecteur3D& bodyAnchor, Rigidbody* otherRigidbody, const Vecteur3D otherAnchor, float mk, float restlength);

	//Destructeur
	~SpringForceGenerator();


	//Transform each anchor point in world coordinate, 
	// calculate the spring force and apply it at anchor point
	void UpdateForce(Rigidbody* rigidbody) override;

};

#endif