#pragma once

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Maths/Vecteur3D.h"
#include "CoreECS/Coordinator.h"
#include "Object3D.h"
#include "Maths/Matrix34.h"


class Rigidbody
{
private:
	Entity entity;

	float inverseMasse;
	float m_linearDamping;
	float m_angularDamping;
	Vecteur3D m_forceAccum;
	Vecteur3D m_torqueAccum;
	Vecteur3D velocity;
	Vecteur3D rotation;
	Vecteur3D accel_lineaire;
	Vecteur3D accel_rotation;
	Matrix3D inertie;
	Matrix3D inertie_transfo;

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
	Rigidbody(Entity entityParent, float angularDamping, float invmasse, float linearDamping, ObjectTypeEnum type_objet,Vecteur3D vitesse);

	/// <summary>
	/// Constructeur de copie
	/// </summary>
	/// <param name="rb"> Le rigidbody que l'on souhaite copier </param>
	//Rigidbody(const Rigidbody& rb);

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
	/// Getter velocity
	/// </summary>
	/// <returns> velocity </returns>
	Vecteur3D getVelocity() const { return velocity; };

	/// <summary>
	/// Getter rotation
	/// </summary>
	/// <returns> Le vecteur 3D représentant la vitesse angulaire suivant les 3 axes </returns>
	Vecteur3D getRotation() const { return rotation; };

	/// <summary>
	/// Getter position
	/// </summary>
	/// <returns> Un vecteur 3D représentation la position du rb dans la scène </returns>
	Vecteur3D getPos() const;

	/// <summary>
	/// Getter orientation
	/// </summary>
	/// <returns> Un quaternion représentant l'orientation de l'objet dans la scène </returns>
	Quaternion getOrientation() const;

	/// <summary>
	/// Getter Model Matrix
	/// </summary>
	/// <returns> La model Matrix du rb </returns>
	Matrix34 getModelMatrix() const;

	/// <summary>
	/// Setter velocity
	/// </summary>
	/// <param name="velocity"> Un vecteur 3D de la vitesse à set au rb </param>
	void setVelocity(const Vecteur3D Velocity);

	/// <summary>
	/// Setter rotation
	/// </summary>
	/// <param name="Rotation"> Un vecteur3D de la vitesse angulaire à set au rb </param>
	void setRotation(const Vecteur3D Rotation);

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

	/// <summary>
	/// Convertis les coordonnées d'un point en local en global
	/// </summary>
	/// <param name="localPoint"> La position du point à convertir </param>
	/// <returns> La position du point en coordonnées globales </returns>
	Vecteur3D convertToWorld(const Vecteur3D& localPoint);
};

#endif
