#ifndef PARTICULE_H
#define PARTICULE_H

#include "Maths/Vector3D.h"
#include "CoreECS/Coordinator.h"

class Particule 
{
	public:
		//Constructeurs//
		Particule() {}
		Particule(Entity entityParent, Vector3D vel_initiale, float r, float m);
		Particule(const Particule &p);

		//Getters//

		float getInverseMasse() const { return InverseMasse; }
		float getRayon() const { return rayon; }
		Vector3D getPos() const;
		Vector3D getVelocity() const { return velocity; }
		Vector3D getAcc() const { return acceleration; }
	
		//Setters//
		void setPos(const Vector3D);
		void setVelocity(const Vector3D);
		void setAcceleration(const Vector3D);

		/**
		* Fonction qui mets à jour la position de la particule en fonction du temps
		*/
		void update(float h = 1.0f / 60.0f);

		/*
		* Fonction d'ajout de force à la particule
		*/
		void addForce(const Vector3D&);

		/*
		* Fonction de nettoyage de l'accumulateur
		*/
		void clearAccum();

	private:
		Entity entity;
		Vector3D velocity;
		Vector3D acceleration;
		float rayon;
		float InverseMasse;

		//Accumulateur de forces
		Vector3D AccumForce;

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
