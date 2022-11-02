#ifndef PARTICULE_H
#define PARTICULE_H

#include "Maths/Vecteur3D.h"
#include "CoreECS/Coordinator.h"

class Particule 
{
public:
	//Constructeurs//
	Particule() {}
	Particule(Entity entityParent, Vecteur3D vel_initiale, float r, float m);
	Particule(const Particule &p);

	//Getters//

	float getInverseMasse() const { return InverseMasse; }
	float getRayon() const { return rayon; }
	Vecteur3D getPos() const;
	Vecteur3D getVelocity() const { return velocity; }
	Vecteur3D getAcc() const { return acceleration; }
	
	//Setters//
	void setPos(const Vecteur3D);
	void setVelocity(const Vecteur3D);
	void setAcceleration(const Vecteur3D);

	/**
	* Fonction qui mets à jour la position de la particule en fonction du temps
	*/
	void update(float h = 1.0f / 60.0f);

	/*
	* Fonction d'ajout de force à la particule
	*/
	void addForce(const Vecteur3D&);

	/*
	* Fonction de nettoyage de l'accumulateur
	*/
	void clearAccum();

private:
	Entity entity;
	Vecteur3D velocity;
	Vecteur3D acceleration;
	float rayon;
	float InverseMasse;

	//Accumulateur de forces
	Vecteur3D AccumForce;

	//Constante de gravité
	static float g;
	//Valeur des frottements
	static float d;
	//Hauteur du sol
	static float sol;

	//Fonctions d'update

	/**
	* Mets à jour la position de la particule en fonction du frame rate
	*/
	void updatePosition(float frameRate);

	/**
	* Mets à jour la vélocité de la particule en fonction du frame rate
	*/
	void updateVelocity(float frameRate);

};

#endif
