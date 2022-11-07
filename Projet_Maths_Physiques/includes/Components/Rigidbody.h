#pragma once

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Maths/Vecteur3D.h"
#include "CoreECS/Coordinator.h"


class Rigidbody
{
private:
	Entity entity;

	float inverseMasse;
	float m_linearDamping;
	float m_angularDamping;
	Vecteur3D m_forceAccum;
	Vecteur3D m_torqueAccum;

	/// <summary>
	/// Call each frame to calculate the transformMatrix and normalize the orientation
	/// </summary>
	void CalculateDerivatedData();

public:
	/// <summary>
	/// Constructeur non valué
	/// </summary>
	Rigidbody() {}

	/// <summary>
	/// Constructeur valué
	/// </summary>
	/// <param name="entityParent"> Entité parente pour le modèle ECS </param>
	/// <param name="angularDamping"> La valeur de m_angularDamping </param>
	Rigidbody(Entity entityParent, float angularDamping);

	/// <summary>
	/// Constructeur de copie
	/// </summary>
	/// <param name="rb"> Le rigidbody que l'on souhaite copier </param>
	Rigidbody(const Rigidbody& rb);

	/// <summary>
	/// Getter inverseMasse
	/// </summary>
	/// <returns> inverseMasse </returns>
	float getinverseMasse() const { return inverseMasse; };

	/// <summary>
	/// Getter m_linearDamping
	/// </summary>
	/// <returns> m_linearDamping </returns>
	float getLinearDamping() const { return m_linearDamping; };

	/// <summary>
	/// Getter m_angularDamping
	/// </summary>
	/// <returns> m_angularDamping </returns>
	float getAngularDamping() const { return m_angularDamping; };

	/// <summary>
	/// Getter m_forceAccum
	/// </summary>
	/// <returns> m_forceAccum </returns>
	Vecteur3D getForceAccum() const { return m_forceAccum; };

	/// <summary>
	/// Getter m_torqueAccum
	/// </summary>
	/// <returns> m_torqueAccum </returns>
	Vecteur3D getTorqueAccum() const { return m_torqueAccum; };

	/// <summary>
	/// Add force on the Center of mass but no torque is generated
	/// </summary>
	/// <param name="force"> Vecteur3D de la force </param>
	void addForce(const Vecteur3D& force);

	/// <summary>
	/// Add force at a point in world coordinate, generate force and torque 
	/// </summary>
	/// <param name="force"> La force que l'on souhaite add </param>
	/// <param name="worldPoint"> Le point du monde sur lequel s'exerce la force ? </param>
	void addForceAtPoint(const Vecteur3D& force, const Vecteur3D& worldPoint);

	/// <summary>
	/// Add force at a point in local coordinate 
	/// The point is converted in world coordinated by using the transform matrix
	/// Generate force and torque
	/// </summary>
	/// <param name="force"> La force que l'on souhaite add </param>
	/// <param name="LocalPoint"> </param>
	void addForceAtBodyPoint(const Vecteur3D& force, const Vecteur3D& LocalPoint);

	/// <summary>
	/// Called each frame to reset m_forceAccum & m_torqueAccum
	/// </summary>
	void clearAccumulator();

	/// <summary>
	/// Integrate the rigidbody by modifying position, orientation and velocities
	/// </summary>
	/// <param name="duration"> time->deltaTime() je suppose </param>
	void Integrate(float duration);
};

#endif
