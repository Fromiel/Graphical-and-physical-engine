#pragma once
#ifndef PARTICULE_H
#define PARTICULE_H

#include "Vecteur3D.h"

class Particule {
public:
	//Constructeurs//

	Particule(Vecteur3D pos_initiale, Vecteur3D vel_initiale, double r, double m);
	Particule(const Particule &p);

	//Getters//

	double getInverseMasse() const { return InverseMasse; }
	double getRayon() const { return rayon; }
	Vecteur3D getPos() const { return position; }
	Vecteur3D getVelocity() const { return velocity; }
	Vecteur3D getAcc() const { return acceleration; }
	
	//Setters//
	
	void setPos(const Vecteur3D);
	void setVelocity(const Vecteur3D);
	void setAcceleration(const Vecteur3D);

	/**
	* Fonction qui mets à jour la position de la particule en fonction du temps
	*/
	void update(double h = 1.0/60.0);

private:
	Vecteur3D position;
	Vecteur3D velocity;
	Vecteur3D acceleration;
	double rayon;
	double InverseMasse;

	//Constante de gravité
	static double g;
	//Valeur des frottements
	static double d;
	//Hauteur du sol
	static double sol;

	//Fonctions d'update

	/**
	* Mets à jour la position de la particule en fonction du frame rate
	*/
	void updatePosition(double frameRate);

	/**
	* Mets à jour la vélocité de la particule en fonction du frame rate
	*/
	void updateVelocity(double frameRate);

};

#endif
