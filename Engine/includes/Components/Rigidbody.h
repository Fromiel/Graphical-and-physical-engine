#pragma once

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Maths/Vector3D.h"
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
	Vector3D m_forceAccum;
	Vector3D m_torqueAccum;
	Vector3D velocity;
	Vector3D rotation;
	Vector3D accel_lineaire;
	Vector3D accel_rotation;
	Matrix3D inertie;
	Matrix3D inertie_transfo;

	/// <summary>
	/// Call each frame to calculate the transformMatrix and normalize the orientation
	/// </summary>
	void CalculateDerivatedData();

public:
	/// <summary>
	/// Constructeur non valu�
	/// </summary>
	Rigidbody() {}

	/// <summary>
	/// Constructeur valu�
	/// </summary>
	/// <param name="entityParent">Entit� parente pour le mod�le ECS</param>
	/// <param name="angularDamping">La valeur de m_angularDamping</param>
	/// <param name="invmasse"></param>
	/// <param name="linearDamping"></param>
	/// <param name="type_objet"></param>
	/// <param name="vitesse"></param>
	Rigidbody(Entity entityParent, float angularDamping, float invmasse, float linearDamping, ObjectTypeEnum type_objet,Vector3D vitesse = Vector3D(), Vector3D vitesse_angu = Vector3D());

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
	Vector3D getForceAccum() const { return m_forceAccum; };

	/// <summary>
	/// Getter m_torqueAccum
	/// </summary>
	/// <returns> m_torqueAccum </returns>
	Vector3D getTorqueAccum() const { return m_torqueAccum; };

	/// <summary>
	/// Getter velocity
	/// </summary>
	/// <returns> velocity </returns>
	Vector3D getVelocity() const { return velocity; };

	/// <summary>
	/// Getter rotation
	/// </summary>
	/// <returns> Le vecteur 3D repr�sentant la vitesse angulaire suivant les 3 axes </returns>
	Vector3D getRotation() const { return rotation; };

	/// <summary>
	/// Getter position
	/// </summary>
	/// <returns> Un vecteur 3D repr�sentation la position du rb dans la sc�ne </returns>
	Vector3D getPos() const;

	/// <summary>
	/// Getter orientation
	/// </summary>
	/// <returns> Un quaternion repr�sentant l'orientation de l'objet dans la sc�ne </returns>
	Quaternion getOrientation() const;

	/// <summary>
	/// Getter Model Matrix
	/// </summary>
	/// <returns> La model Matrix du rb </returns>
	Matrix34 getModelMatrix() const;

	/// <summary>
	/// Setter velocity
	/// </summary>
	/// <param name="velocity"> Un vecteur 3D de la vitesse � set au rb </param>
	void setVelocity(const Vector3D Velocity);

	/// <summary>
	/// Setter rotation
	/// </summary>
	/// <param name="Rotation"> Un vecteur3D de la vitesse angulaire � set au rb </param>
	void setRotation(const Vector3D Rotation);

	/// <summary>
	/// Add force on the Center of mass but no torque is generated
	/// </summary>
	/// <param name="force"> Vecteur3D de la force </param>
	void addForce(const Vector3D& force);

	/// <summary>
	/// Add force at a point in world coordinate, generate force and torque 
	/// </summary>
	/// <param name="force"> La force que l'on souhaite add </param>
	/// <param name="worldPoint"> Le point du monde sur lequel s'exerce la force ? </param>
	void addForceAtPoint(const Vector3D& force, const Vector3D& worldPoint);

	/// <summary>
	/// Add force at a point in local coordinate 
	/// The point is converted in world coordinated by using the transform matrix
	/// Generate force and torque
	/// </summary>
	/// <param name="force"> La force que l'on souhaite add </param>
	/// <param name="LocalPoint"> </param>
	void addForceAtBodyPoint(const Vector3D& force, const Vector3D& LocalPoint);

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
	/// Convertis les coordonn�es d'un point en local en global
	/// </summary>
	/// <param name="localPoint"> La position du point � convertir </param>
	/// <returns> La position du point en coordonn�es globales </returns>
	Vector3D convertToWorld(const Vector3D& localPoint);
};

#endif
